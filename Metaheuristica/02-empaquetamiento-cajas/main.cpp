// Laboratorio 04 (2024-2): empaquetamiento de objetos en cajas.
// Objetivo: MINIMIZAR el numero de cajas de capacidad 10 kg.
// Merito voraz: objetos de mayor peso que aun caben en la caja actual.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.30;
const int ITERACIONES = 1000;
struct Objeto { char id; int peso; };
struct Caja { int id, libre; vector<Objeto> objetos; };
struct Solucion { vector<Caja> cajas; bool completa; };

bool hayPendientes(const vector<bool> &usado) {
    for (bool estado : usado) if (!estado) return true;
    return false;
}

// Una sola RCL por caja, entre objetos no usados que caben en su espacio libre.
vector<int> construirRCL(const vector<Objeto> &objetos,
                         const vector<bool> &usado, int libre) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;
    for (int i = 0; i < (int)objetos.size(); ++i) {
        if (usado[i] || objetos[i].peso > libre) continue;
        candidatos.push_back(i);
        if (objetos[i].peso > mejor) mejor = objetos[i].peso;
        if (objetos[i].peso < peor) peor = objetos[i].peso;
    }
    if (candidatos.empty()) return rcl;
    double umbral = mejor - ALFA * (mejor - peor);
    for (int i : candidatos)
        if (objetos[i].peso >= umbral) rcl.push_back(i);
    return rcl;
}

Solucion construirSolucion(const vector<Objeto> &objetos, int capacidad) {
    // Un objeto mas pesado que la caja haria imposible una asignacion completa.
    for (const Objeto &o : objetos)
        if (o.peso > capacidad || o.peso < 0) return {{}, false};
    vector<bool> usado(objetos.size(), false);
    vector<Caja> cajas;
    while (hayPendientes(usado)) {
        Caja caja = {(int)cajas.size() + 1, capacidad, {}};
        while (true) {
            vector<int> rcl = construirRCL(objetos, usado, caja.libre);
            if (rcl.empty()) break; // Cerrar caja; intentar otra si quedan objetos.
            int indice = rcl[rand() % rcl.size()];
            usado[indice] = true;
            caja.libre -= objetos[indice].peso;
            caja.objetos.push_back(objetos[indice]);
        }
        if (caja.objetos.empty()) return {{}, false}; // Evitar bucle infinito.
        cajas.push_back(caja);
    }
    return {cajas, true};
}

int main() {
    srand(42);
    vector<Objeto> objetos = {{'A',4},{'B',8},{'C',1},
                              {'D',4},{'E',2},{'F',1}};
    int capacidad = 10;
    Solucion mejor = {{}, false};
    for (int iter = 0; iter < ITERACIONES; ++iter) {
        Solucion actual = construirSolucion(objetos, capacidad);
        if (actual.completa && (!mejor.completa || actual.cajas.size() < mejor.cajas.size()))
            mejor = actual;
    }
    if (!mejor.completa) {
        cout << "No existe una distribucion factible.\n";
        return 0;
    }
    cout << "Minimo de cajas encontrado: " << mejor.cajas.size() << "\n";
    for (const Caja &caja : mejor.cajas) {
        cout << "Caja " << caja.id << " (" << capacidad - caja.libre
             << "/" << capacidad << " kg):";
        for (const Objeto &o : caja.objetos) cout << " " << o.id;
        cout << "\n";
    }
}
