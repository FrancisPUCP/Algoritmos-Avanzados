// Laboratorio 04 (2026-1): seleccion de proyectos con presupuesto limitado.
// Objetivo: MAXIMIZAR ganancias, respetando el costo y las dependencias.
// Merito heuristico: ganancia propia + ganancia de proyectos sucesores directos.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.30;
const int ITERACIONES = 1000;
struct Proyecto {
    int id, costo, ganancia;
    vector<int> predecesores; // IDs requeridos antes de seleccionar este proyecto.
};
struct Solucion {
    vector<int> elegidos;
    int gananciaTotal, costoTotal;
};

// Los IDs del conjunto de prueba son consecutivos desde 1.
bool esFactible(const Proyecto &p, const vector<bool> &seleccionado,
                int presupuestoLibre) {
    if (seleccionado[p.id - 1] || p.costo > presupuestoLibre) return false;
    for (int pred : p.predecesores)
        if (!seleccionado[pred - 1]) return false;
    return true;
}

// Heuristica de desbloqueo: considerar ganancias de sucesores inmediatos.
int calcularMerito(const Proyecto &p, const vector<Proyecto> &proyectos) {
    int merito = p.ganancia;
    for (const Proyecto &otro : proyectos) {
        for (int predecesor : otro.predecesores) {
            if (predecesor == p.id) {
                merito += otro.ganancia;
                break;
            }
        }
    }
    return merito;
}

vector<int> construirRCL(const vector<Proyecto> &proyectos,
                         const vector<bool> &seleccionado, int presupuestoLibre) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;
    for (int i = 0; i < (int)proyectos.size(); ++i) {
        if (!esFactible(proyectos[i], seleccionado, presupuestoLibre)) continue;
        int merito = calcularMerito(proyectos[i], proyectos);
        candidatos.push_back(i);
        if (merito > mejor) mejor = merito;
        if (merito < peor) peor = merito;
    }
    if (candidatos.empty()) return rcl;
    double umbral = mejor - ALFA * (mejor - peor);
    for (int i : candidatos)
        if (calcularMerito(proyectos[i], proyectos) >= umbral) rcl.push_back(i);
    return rcl;
}

Solucion construirSolucion(const vector<Proyecto> &proyectos, int presupuesto) {
    Solucion sol = {{}, 0, 0};
    vector<bool> seleccionado(proyectos.size(), false);
    int libre = presupuesto;
    while (true) {
        vector<int> rcl = construirRCL(proyectos, seleccionado, libre);
        if (rcl.empty()) break; // No queda proyecto actualmente factible.
        int elegido = rcl[rand() % rcl.size()];
        const Proyecto &p = proyectos[elegido];
        libre -= p.costo;
        sol.costoTotal += p.costo;
        sol.gananciaTotal += p.ganancia; // Objetivo real, NO el merito de la RCL.
        sol.elegidos.push_back(p.id);
        seleccionado[p.id - 1] = true;
    }
    return sol;
}

int main() {
    srand(42);
    vector<Proyecto> proyectos = {
        {1,100,200,{}}, {2,50,300,{1}}, {3,150,300,{1}},
        {4,50,400,{}}, {5,50,200,{4}}, {6,150,800,{2,4}},
        {7,100,250,{}}
    };
    int presupuesto = 400;
    Solucion mejor = {{}, INT_MIN, 0};
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(proyectos, presupuesto);
        if (actual.gananciaTotal > mejor.gananciaTotal) mejor = actual;
    }
    cout << "Mayor ganancia: " << mejor.gananciaTotal << "\n";
    cout << "Presupuesto usado: " << mejor.costoTotal << "/" << presupuesto << "\n";
    cout << "Proyectos seleccionados:";
    for (int id : mejor.elegidos) cout << " " << id;
    cout << "\n";
}
