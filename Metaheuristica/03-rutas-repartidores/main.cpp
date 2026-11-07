// Laboratorio 04 (2024-2): ruta de reparto entre puntos conectados.
// Objetivo: MAXIMIZAR la ganancia total sin repetir puntos y respetando aristas.
// La ruta comienza en A; cada movimiento debe ser un destino permitido.
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

const double ALFA = 0.40;
const int ITERACIONES = 10000;
struct Punto { char id; int ganancia; vector<char> destinos; };
struct Solucion { vector<char> ruta; int gananciaTotal; };

bool esFactible(const vector<Punto> &puntos, int actual, int destino) {
    for (char permitido : puntos[actual].destinos)
        if (permitido == puntos[destino].id) return true;
    return false;
}

// Filtrar destinos accesibles no visitados y favorecer mayor ganancia inmediata.
vector<int> construirRCL(const vector<Punto> &puntos, int actual,
                         const vector<bool> &visitado) {
    vector<int> candidatos, rcl;
    int mejor = INT_MIN, peor = INT_MAX;
    for (int i = 0; i < (int)puntos.size(); ++i) {
        if (visitado[i] || !esFactible(puntos, actual, i)) continue;
        candidatos.push_back(i);
        if (puntos[i].ganancia > mejor) mejor = puntos[i].ganancia;
        if (puntos[i].ganancia < peor) peor = puntos[i].ganancia;
    }
    if (candidatos.empty()) return rcl;
    double umbral = mejor - ALFA * (mejor - peor);
    for (int i : candidatos)
        if (puntos[i].ganancia >= umbral) rcl.push_back(i);
    return rcl;
}

Solucion construirSolucion(const vector<Punto> &puntos) {
    Solucion sol = {{'A'}, 0};
    vector<bool> visitado(puntos.size(), false);
    int actual = 0; // A se encuentra en la posicion 0.
    visitado[actual] = true;
    while (true) {
        vector<int> rcl = construirRCL(puntos, actual, visitado);
        if (rcl.empty()) break; // No quedan movimientos factibles.
        int elegido = rcl[rand() % rcl.size()];
        sol.gananciaTotal += puntos[elegido].ganancia;
        sol.ruta.push_back(puntos[elegido].id);
        visitado[elegido] = true;
        actual = elegido;
    }
    return sol;
}

int main() {
    srand(42);
    vector<Punto> puntos = {
        {'A',0, {'B','C','D','E','H'}},
        {'B',20,{'C','D','F','H'}},
        {'C',30,{'F'}}, {'D',40,{}},
        {'E',40,{'C','F','G'}}, {'F',40,{}},
        {'G',10,{}}, {'H',50,{}}
    };
    Solucion mejor = {{}, INT_MIN};
    for (int i = 0; i < ITERACIONES; ++i) {
        Solucion actual = construirSolucion(puntos);
        if (actual.gananciaTotal > mejor.gananciaTotal) mejor = actual;
    }
    cout << "Mayor ganancia encontrada: " << mejor.gananciaTotal << "\nRuta:";
    for (char destino : mejor.ruta) cout << " " << destino;
    cout << "\n";
}
