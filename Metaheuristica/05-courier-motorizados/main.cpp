// Laboratorio 04 (2025-2): asignar un motorizado a cada ciudad.
// Cada envio cuesta transporte fijo + costo del motorizado asignado.
// Objetivo: MINIMIZAR el costo total, con costo por ciudad <= K = 20.
// Se admite reutilizar un motorizado en distintas ciudades.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.30;
const int ITERACIONES = 1000;
struct Ciudad { int id, costoTransporte; vector<int> costosMotorizados; };
struct Solucion { vector<int> asignaciones; int costoTotal; bool completa; };

bool esFactible(const Ciudad &ciudad, int motorizado, int K) {
    return ciudad.costoTransporte + ciudad.costosMotorizados[motorizado] <= K;
}

// RCL de MINIMIZACION: solo costos <= mejor + alfa*(peor-mejor).
vector<int> construirRCL(const Ciudad &ciudad, int K) {
    vector<int> candidatos, rcl;
    int mejor = INT_MAX, peor = INT_MIN;
    for (int i = 0; i < (int)ciudad.costosMotorizados.size(); ++i) {
        if (!esFactible(ciudad, i, K)) continue;
        int costo = ciudad.costoTransporte + ciudad.costosMotorizados[i];
        candidatos.push_back(i);
        if (costo < mejor) mejor = costo;
        if (costo > peor) peor = costo;
    }
    if (candidatos.empty()) return rcl;
    double umbral = mejor + ALFA * (peor - mejor);
    for (int i : candidatos) {
        int costo = ciudad.costoTransporte + ciudad.costosMotorizados[i];
        if (costo <= umbral) rcl.push_back(i);
    }
    return rcl;
}

Solucion construirSolucion(const vector<Ciudad> &ciudades, int K) {
    Solucion sol = {{}, 0, true};
    for (const Ciudad &ciudad : ciudades) {
        vector<int> rcl = construirRCL(ciudad, K);
        if (rcl.empty()) return {{}, INT_MAX, false};
        int elegido = rcl[rand() % rcl.size()]; // Indice desde cero.
        sol.asignaciones.push_back(elegido);
        sol.costoTotal += ciudad.costoTransporte + ciudad.costosMotorizados[elegido];
    }
    return sol;
}

int main() {
    srand(42);
    vector<Ciudad> ciudades = {
        {1,16,{3,5,7,8,4}},
        {2,15,{4,2,5,7,3}},
        {3,12,{5,3,4,5,7}},
        {4,18,{6,4,2,1,5}}
    };
    int K = 20;
    Solucion mejor = {{}, INT_MAX, false};
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(ciudades, K);
        if (actual.completa && actual.costoTotal < mejor.costoTotal)
            mejor = actual;
    }
    if (!mejor.completa) {
        cout << "No hay asignacion factible.\n";
        return 0;
    }
    cout << "Menor costo total: S/ " << mejor.costoTotal << "\n";
    for (int i = 0; i < (int)ciudades.size(); ++i) {
        cout << "Ciudad " << ciudades[i].id << " -> Motorizado "
             << mejor.asignaciones[i] + 1 << "\n";
    }
}
