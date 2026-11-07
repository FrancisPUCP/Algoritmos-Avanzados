// Laboratorio 04 (2024-1): asignacion de tablas a discos.
// Objetivo: MAXIMIZAR la menor velocidad (IOPS) restante entre los discos.
// Heuristica: RCL de tablas con alta demanda de IOPS; asignar cada una
// al disco factible que conserve mas IOPS despues de la asignacion.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.30;
const int ITERACIONES = 10000;

struct Tabla { int id, gb, iops; };
struct Disco {
    int id, gbLibres, iopsLibres;
    vector<int> tablas; // Identificadores de tablas ya asignadas.
};
struct Solucion {
    vector<Disco> discos;
    int velocidadMinima;
    bool completa;
};

// Dos restricciones simultaneas: capacidad de almacenamiento y rendimiento.
bool esFactible(const Disco &disco, const Tabla &tabla) {
    return tabla.gb <= disco.gbLibres && tabla.iops <= disco.iopsLibres;
}

// Devuelve el indice del disco que deja mas IOPS libres, o -1 si no existe.
int buscarMejorDisco(const vector<Disco> &discos, const Tabla &tabla) {
    int mejor = -1;
    for (int i = 0; i < (int)discos.size(); ++i) {
        if (!esFactible(discos[i], tabla)) continue;
        if (mejor == -1 || discos[i].iopsLibres > discos[mejor].iopsLibres)
            mejor = i;
    }
    return mejor;
}

// Construye UNA lista restringida: solo tablas pendientes con disco factible.
vector<int> construirRCL(const vector<Tabla> &tablas,
                         const vector<Disco> &discos,
                         const vector<bool> &usado) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;
    for (int i = 0; i < (int)tablas.size(); ++i) {
        if (usado[i] || buscarMejorDisco(discos, tablas[i]) == -1) continue;
        candidatos.push_back(i);
        if (tablas[i].iops > mejor) mejor = tablas[i].iops;
        if (tablas[i].iops < peor) peor = tablas[i].iops;
    }
    if (candidatos.empty()) return rcl;
    // Maximizar el merito: aceptar demandas >= umbral.
    double umbral = mejor - ALFA * (mejor - peor);
    for (int indice : candidatos)
        if (tablas[indice].iops >= umbral) rcl.push_back(indice);
    return rcl;
}

// Evaluacion GLOBAL: importa el peor disco de la solucion, no la suma de IOPS.
int evaluar(const vector<Disco> &discos) {
    int minimo = INT_MAX;
    for (const Disco &d : discos)
        if (d.iopsLibres < minimo) minimo = d.iopsLibres;
    return minimo;
}

Solucion construirSolucion(const vector<Tabla> &tablas,
                          const vector<Disco> &discosIniciales) {
    vector<Disco> discos = discosIniciales; // Cada iteracion arranca de cero.
    vector<bool> usado(tablas.size(), false);
    for (int paso = 0; paso < (int)tablas.size(); ++paso) {
        vector<int> rcl = construirRCL(tablas, discos, usado);
        if (rcl.empty()) return {{}, INT_MIN, false}; // Incompleta: se descarta.
        int elegido = rcl[rand() % rcl.size()];
        int d = buscarMejorDisco(discos, tablas[elegido]);
        discos[d].gbLibres -= tablas[elegido].gb;
        discos[d].iopsLibres -= tablas[elegido].iops;
        discos[d].tablas.push_back(tablas[elegido].id);
        usado[elegido] = true;
    }
    return {discos, evaluar(discos), true};
}

int main() {
    srand(42); // Semilla fija: facilita repetir y revisar los resultados.
    vector<Tabla> tablas = {
        {1,20,150}, {2,10,100}, {3,15,80},
        {4,100,50}, {5,50,120}, {6,100,10}
    };
    vector<Disco> discos = {
        {1,800,250,{}}, {2,750,200,{}}, {3,850,200,{}}
    };
    Solucion mejor = {{}, INT_MIN, false};
    // GRASP multarranque: conservar la solucion de mayor minimo.
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(tablas, discos);
        if (actual.completa && actual.velocidadMinima > mejor.velocidadMinima)
            mejor = actual;
    }
    if (!mejor.completa) {
        cout << "No se encontro una asignacion completa.\n";
        return 0;
    }
    cout << "Mayor velocidad minima: " << mejor.velocidadMinima << " IOPS\n";
    for (const Disco &d : mejor.discos) {
        cout << "Disco " << d.id << " | Tablas:";
        for (int id : d.tablas) cout << " " << id;
        cout << " | IOPS libres: " << d.iopsLibres << "\n";
    }
}
