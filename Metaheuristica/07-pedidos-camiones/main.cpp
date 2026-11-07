// Laboratorio 04 (2026-1): empacar pedidos en camiones de capacidad 50 kg.
// Objetivo: MINIMIZAR el numero de camiones necesarios para todos los pedidos.
// Merito voraz: asignar primero pedidos pesados que aun caben en el camion.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.20;
const int ITERACIONES = 1000;
struct Pedido { char id; int peso; };
struct Camion { vector<int> indicesPedidos; int pesoUtilizado; };
struct Solucion { vector<Camion> camiones; bool completa; };

bool hayPendientes(const vector<bool> &usado) {
    for (bool x : usado) if (!x) return true;
    return false;
}

// RCL por camion entre pedidos no utilizados que aun caben.
vector<int> construirRCL(const vector<Pedido> &pedidos,
                         const vector<bool> &usado, int espacioLibre) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;
    for (int i = 0; i < (int)pedidos.size(); ++i) {
        if (usado[i] || pedidos[i].peso > espacioLibre) continue;
        candidatos.push_back(i);
        if (pedidos[i].peso > mejor) mejor = pedidos[i].peso;
        if (pedidos[i].peso < peor) peor = pedidos[i].peso;
    }
    if (candidatos.empty()) return rcl;
    double umbral = mejor - ALFA * (mejor - peor);
    for (int i : candidatos)
        if (pedidos[i].peso >= umbral) rcl.push_back(i);
    return rcl;
}

Solucion construirSolucion(const vector<Pedido> &pedidos, int capacidad) {
    for (const Pedido &p : pedidos)
        if (p.peso > capacidad || p.peso < 0) return {{}, false};
    vector<bool> usado(pedidos.size(), false);
    vector<Camion> camiones;
    while (hayPendientes(usado)) {
        Camion camion = {{}, 0};
        while (true) {
            vector<int> rcl = construirRCL(pedidos, usado, capacidad - camion.pesoUtilizado);
            if (rcl.empty()) break;
            int elegido = rcl[rand() % rcl.size()];
            camion.indicesPedidos.push_back(elegido);
            camion.pesoUtilizado += pedidos[elegido].peso;
            usado[elegido] = true;
        }
        if (camion.indicesPedidos.empty()) return {{}, false};
        camiones.push_back(camion);
    }
    return {camiones, true};
}

int main() {
    srand(42);
    vector<Pedido> pedidos = {
        {'A',15}, {'B',32}, {'C',20},
        {'D',42}, {'E',8}, {'F',18}
    };
    int capacidad = 50;
    Solucion mejor = {{}, false};
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(pedidos, capacidad);
        if (actual.completa && (!mejor.completa || actual.camiones.size() < mejor.camiones.size()))
            mejor = actual;
    }
    if (!mejor.completa) {
        cout << "No existe una asignacion factible.\n";
        return 0;
    }
    cout << "Menor cantidad de camiones encontrada: " << mejor.camiones.size() << "\n";
    for (int i = 0; i < (int)mejor.camiones.size(); ++i) {
        cout << "Camion " << i + 1 << " (" << mejor.camiones[i].pesoUtilizado
             << "/" << capacidad << " kg):";
        for (int p : mejor.camiones[i].indicesPedidos) cout << " " << pedidos[p].id;
        cout << "\n";
    }
}
