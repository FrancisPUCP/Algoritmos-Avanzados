// Laboratorio 04 (2025-1): produccion de botellas, PARTE B.
// Objetivo: MINIMIZAR makespan = MAXIMO de las cargas de las cinco lineas.
// Criterio GRASP: B: prioridad ascendente, despues cantidad de botellas.
// Modelo del ejercicio: cada botella agrega 6 minutos a la linea asignada.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.30;       // Valor de practica; el enunciado no fija alfa.
const int ITERACIONES = 1000;   // Valor de practica.
const int MINUTOS_POR_BOTELLA = 6;
struct Orden { int id, botellas, prioridad; };
struct Linea { int id, tiempoAcumulado; vector<int> ordenes; };
struct Solucion { vector<Linea> lineas; int makespan; };

vector<int> construirRCL(const vector<Orden> &ordenes,
                         const vector<bool> &usado) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;

    // PRIORIDAD estricta: 1 es mas importante que 2 y 3.
    int prioridadMayor = INT_MAX;
    for (int i = 0; i < (int)ordenes.size(); ++i)
        if (!usado[i] && ordenes[i].prioridad < prioridadMayor)
            prioridadMayor = ordenes[i].prioridad;

    for (int i = 0; i < (int)ordenes.size(); ++i) {
        if (usado[i] || ordenes[i].prioridad != prioridadMayor) continue;
        candidatos.push_back(i);
        if (ordenes[i].botellas > mejor) mejor = ordenes[i].botellas;
        if (ordenes[i].botellas < peor) peor = ordenes[i].botellas;
    }
    if (candidatos.empty()) return rcl;
    // Una sola RCL, privilegiando las ordenes mas grandes del grupo elegible.
    double umbral = mejor - ALFA * (mejor - peor);
    for (int i : candidatos)
        if (ordenes[i].botellas >= umbral) rcl.push_back(i);
    return rcl;
}

// Elegir la linea menos ocupada sin reordenar ni perder sus identificadores.
int buscarLineaMenosCargada(const vector<Linea> &lineas) {
    int elegida = 0;
    for (int i = 1; i < (int)lineas.size(); ++i)
        if (lineas[i].tiempoAcumulado < lineas[elegida].tiempoAcumulado)
            elegida = i;
    return elegida;
}

int calcularMakespan(const vector<Linea> &lineas) {
    int maximo = 0;
    for (const Linea &linea : lineas)
        if (linea.tiempoAcumulado > maximo) maximo = linea.tiempoAcumulado;
    return maximo;
}

Solucion construirSolucion(const vector<Orden> &ordenes, int cantidadLineas) {
    vector<Linea> lineas;
    for (int i = 0; i < cantidadLineas; ++i) lineas.push_back({i + 1, 0, {}});
    vector<bool> usado(ordenes.size(), false);
    // En cada paso se elige una orden mediante RCL, y una linea vorazmente.
    for (int paso = 0; paso < (int)ordenes.size(); ++paso) {
        vector<int> rcl = construirRCL(ordenes, usado);
        int elegido = rcl[rand() % rcl.size()];
        int linea = buscarLineaMenosCargada(lineas);
        lineas[linea].tiempoAcumulado += ordenes[elegido].botellas * MINUTOS_POR_BOTELLA;
        lineas[linea].ordenes.push_back(ordenes[elegido].id);
        usado[elegido] = true;
    }
    return {lineas, calcularMakespan(lineas)};
}

int main() {
    srand(42);
    vector<Orden> ordenes = {
        {1,103,2}, {2,58,1}, {3,88,3}, {4,126,1}, {5,195,2},
        {6,90,2}, {7,54,3}, {8,195,1}, {9,124,2}, {10,113,3},
        {11,193,2}, {12,55,1}, {13,97,1}, {14,97,2}, {15,169,2},
        {16,50,2}, {17,167,3}, {18,74,1}, {19,79,2}, {20,109,1}
    };
    Solucion mejor = {{}, INT_MAX};
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(ordenes, 5);
        if (actual.makespan < mejor.makespan) mejor = actual;
    }
    cout << "Mejor makespan: " << mejor.makespan << " minutos\n";
    for (const Linea &linea : mejor.lineas) {
        cout << "Linea " << linea.id << " (" << linea.tiempoAcumulado << " min):";
        for (int orden : linea.ordenes) cout << " " << orden;
        cout << "\n";
    }
}
