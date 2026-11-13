#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUMIND 20
#define PCRUCE 0.80
#define PCORTE 0.50
#define TSELECCION 0.50

// Cada gen representa si el empleado j realiza la tarea i (matriz aplanada).
// La posición del gen es i*n + j.
bool aberracion(const vector<int> &individuo, int n) {
    if ((int)individuo.size() != n * n) return true;

    // Cada tarea debe quedar asignada exactamente a un empleado.
    for (int i = 0; i < n; i++) {
        int asignacion = 0;
        for (int j = 0; j < n; j++) {
            int indice = i * n + j;
            if (individuo[indice] == 1) asignacion++;
        }
        if (asignacion != 1) return true;
    }

    // Cada empleado debe recibir exactamente una tarea.
    for (int j = 0; j < n; j++) {
        int asignacion = 0;
        for (int i = 0; i < n; i++) {
            int indice = i * n + j;
            if (individuo[indice] == 1) asignacion++;
        }
        if (asignacion != 1) return true;
    }

    return false;
}

// Maximiza la ganancia total de las asignaciones seleccionadas.
int calcularFitness(const vector<int> &individuo,
                    const int ganancia[5][5],
                    int n) {
    if (aberracion(individuo, n)) return 0;

    int fitness = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int indice = i * n + j;
            if (individuo[indice] == 1) {
                fitness += ganancia[i][j];
            }
        }
    }
    return fitness;
}

// Genera asignaciones aleatorias: una elección de empleado por tarea.
// Luego descarta las que no asignan exactamente una tarea a cada empleado.
void generapoblacion(vector<vector<int>> &poblacion, int n) {
    poblacion.clear();
    int intentos = 0;
    const int MAX_INTENTOS = 100000;

    while (poblacion.size() < NUMIND && intentos < MAX_INTENTOS) {
        intentos++;
        vector<int> individuo(n * n, 0);

        for (int i = 0; i < n; i++) {
            int indiceEmpleado = rand() % n;
            int indice = i * n + indiceEmpleado;
            individuo[indice] = 1;
        }

        if (!aberracion(individuo, n)) {
            poblacion.push_back(individuo);
        }
    }
}

// Calcula el fitness de todos los individuos de la población.
void evaluate_population(const vector<vector<int>> &poblacion,
                         vector<int> &fitnessPoblacion,
                         const int ganancia[5][5],
                         int n) {
    fitnessPoblacion.clear();
    for (int i = 0; i < (int)poblacion.size(); i++) {
        fitnessPoblacion.push_back(
            calcularFitness(poblacion[i], ganancia, n)
        );
    }
}

// Ruleta proporcional al fitness; si el total es cero, elige al azar.
int seleccionarPadre(const vector<vector<int>> &poblacion,
                     const vector<int> &fitnessPoblacion) {
    int fitnessTotal = 0;
    for (int fitness : fitnessPoblacion) fitnessTotal += fitness;

    if (fitnessTotal == 0) return rand() % poblacion.size();

    int elegido = rand() % 100;
    double acumulado = 0;
    for (int i = 0; i < (int)fitnessPoblacion.size(); i++) {
        acumulado += fitnessPoblacion[i] * 100.0 / fitnessTotal;
        if (elegido < acumulado) return i;
    }

    return (int)poblacion.size() - 1;
}

// Selecciona TSELECCION de la población para formar el grupo de padres.
void seleccion(const vector<vector<int>> &poblacion,
               const vector<int> &fitnessPoblacion,
               vector<vector<int>> &padres) {
    padres.clear();
    int nPadres = round(poblacion.size() * TSELECCION);

    for (int i = 0; i < nPadres; i++) {
        int indice = seleccionarPadre(poblacion, fitnessPoblacion);
        padres.push_back(poblacion[indice]);
    }
}

// Cruce de un punto: antes del corte toma genes del padre y después de la madre.
void creaHijo(const vector<int> &padre,
              const vector<int> &madre,
              vector<int> &hijo) {
    hijo.clear();
    int pos = round(padre.size() * PCORTE);

    for (int i = 0; i < (int)padre.size(); i++) {
        if (i < pos) hijo.push_back(padre[i]);
        else hijo.push_back(madre[i]);
    }
}

// Considera parejas sin repetir (i < j), aplica PCRUCE y crea dos hijos.
// Solo incorpora los descendientes que cumplen las restricciones.
void casamiento(vector<vector<int>> &poblacion,
                const vector<vector<int>> &padres,
                int n) {
    for (int i = 0; i < (int)padres.size(); i++) {
        for (int j = 0; j < (int)padres.size(); j++) {
            if (i < j) {
                if (rand() % 100 < PCRUCE * 100) {
                    vector<int> hijo1, hijo2;
                    creaHijo(padres[i], padres[j], hijo1);
                    creaHijo(padres[j], padres[i], hijo2);

                    if (!aberracion(hijo1, n)) poblacion.push_back(hijo1);
                    if (!aberracion(hijo2, n)) poblacion.push_back(hijo2);
                }
            }
        }
    }
}

// Imprime los cromosomas y su fitness para revisar cada etapa.
void muestrapoblacion(const vector<vector<int>> &poblacion,
                      const int ganancia[5][5],
                      int n) {
    for (int i = 0; i < (int)poblacion.size(); i++) {
        cout << "Individuo " << i + 1 << ": ";
        for (int gen : poblacion[i]) cout << gen << ' ';
        cout << " | fo=" << calcularFitness(poblacion[i], ganancia, n) << '\n';
    }
}

// Ejecuta las etapas trabajadas: generación, evaluación, selección y cruce.
void genetic_algorithm(const int ganancia[5][5], int n) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion, n);

    vector<int> fitnessPoblacion;
    evaluate_population(poblacion, fitnessPoblacion, ganancia, n);

    cout << "\nPOBLACION INICIAL:\n";
    muestrapoblacion(poblacion, ganancia, n);

    vector<vector<int>> padres;
    seleccion(poblacion, fitnessPoblacion, padres);

    cout << "\nPADRES SELECCIONADOS:\n";
    muestrapoblacion(padres, ganancia, n);

    int cantidadAntes = (int)poblacion.size();
    casamiento(poblacion, padres, n);

    cout << "\nHIJOS GENERADOS: " << poblacion.size() - cantidadAntes << endl;
    evaluate_population(poblacion, fitnessPoblacion, ganancia, n);

    cout << "\nPOBLACION DESPUES DEL CASAMIENTO:\n";
    muestrapoblacion(poblacion, ganancia, n);
}

int main() {
    srand((unsigned)time(nullptr));

    const int ganancia[5][5] = {
        {9, 2, 7, 8, 6},
        {6, 4, 3, 7, 8},
        {5, 8, 1, 8, 3},
        {7, 6, 9, 4, 2},
        {8, 6, 7, 5, 9}
    };

    int n = 5;
    genetic_algorithm(ganancia, n);
    return 0;
}
