#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUMIND 10
#define TSELECCION 0.50

// Datos de cada activo: precio actual y dos escenarios futuros.
struct Activo {
    double precio_actual;
    double precio_futuro_optimista;
    double precio_futuro_pesimista;

    Activo(double pa, double pfo, double pfp)
        : precio_actual(pa),
          precio_futuro_optimista(pfo),
          precio_futuro_pesimista(pfp) {}
};

// Devuelve true si el cromosoma no es válido o supera el presupuesto.
bool aberracion(const vector<int> &individuo,
                const vector<Activo> &activos,
                double presupuesto) {
    if (individuo.size() != activos.size()) return true;

    // Todos los genes deben ser binarios.
    for (int gen : individuo) {
        if (gen != 0 && gen != 1) return true;
    }

    // Solo se suman los precios actuales de los activos seleccionados.
    double costoTotal = 0;
    for (int i = 0; i < (int)activos.size(); i++) {
        if (individuo[i] == 1) costoTotal += activos[i].precio_actual;
    }

    return costoTotal > presupuesto;
}

// Fitness: potencial de ganancia optimista menos impacto pesimista.
double calculafitness(const vector<int> &individuo,
                      const vector<Activo> &activos,
                      double presupuesto) {
    if (aberracion(individuo, activos, presupuesto)) return 0;

    double sumaOptimistas = 0;
    double sumaActuales = 0;
    double sumaPesimistas = 0;

    for (int i = 0; i < (int)individuo.size(); i++) {
        if (individuo[i] == 1) {
            sumaActuales += activos[i].precio_actual;
            sumaOptimistas += activos[i].precio_futuro_optimista;
            sumaPesimistas += activos[i].precio_futuro_pesimista;
        }
    }

    return abs(sumaOptimistas - sumaActuales)
         - abs(sumaPesimistas - sumaActuales);
}

// Genera NUMIND cromosomas binarios y conserva solo los factibles.
void init_population(vector<vector<int>> &poblacion,
                     const vector<Activo> &activos,
                     double presupuesto) {
    poblacion.clear();
    int n = (int)activos.size();
    int contador = 0;

    while (contador < NUMIND) {
        vector<int> individuo(n);
        for (int j = 0; j < n; j++) {
            individuo[j] = rand() % 2;
        }

        if (!aberracion(individuo, activos, presupuesto)) {
            poblacion.push_back(individuo);
            contador++;
        }
    }
}

// Calcula y almacena el fitness de cada individuo, en el mismo orden.
void evaluate_population(const vector<vector<int>> &poblacion,
                         const vector<Activo> &activos,
                         double presupuesto,
                         vector<double> &fitnessPoblacion) {
    fitnessPoblacion.clear();
    for (int i = 0; i < (int)poblacion.size(); i++) {
        fitnessPoblacion.push_back(
            calculafitness(poblacion[i], activos, presupuesto)
        );
    }
}

// Selección por ruleta: devuelve la posición del individuo elegido.
int seleccionarPadre(const vector<vector<int>> &poblacion,
                      const vector<double> &fitnessPoblacion) {
    double fitnessTotal = 0;
    for (double fitness : fitnessPoblacion) {
        fitnessTotal += fitness;
    }

    // Si todos tienen fitness cero, se elige un individuo al azar.
    if (fitnessTotal == 0) return rand() % poblacion.size();

    int elegido = rand() % 100;
    double acumulado = 0;

    for (int i = 0; i < (int)fitnessPoblacion.size(); i++) {
        acumulado += fitnessPoblacion[i] * 100.0 / fitnessTotal;
        if (elegido < acumulado) return i;
    }

    return (int)poblacion.size() - 1;
}

// Selecciona una fracción de la población para formar el conjunto de padres.
void seleccion(const vector<vector<int>> &poblacion,
               const vector<double> &fitnessPoblacion,
               vector<vector<int>> &padres) {
    padres.clear();
    int nPadres = round(poblacion.size() * TSELECCION);

    for (int i = 0; i < nPadres; i++) {
        int pos = seleccionarPadre(poblacion, fitnessPoblacion);
        padres.push_back(poblacion[pos]);
    }
}

// Cruce uniforme: cada gen se hereda aleatoriamente de uno de los padres.
void creaHijo(const vector<int> &padre,
              const vector<int> &madre,
              vector<int> &hijo) {
    hijo.clear();
    for (int i = 0; i < (int)padre.size(); i++) {
        if (rand() % 2 == 0) hijo.push_back(padre[i]);
        else hijo.push_back(madre[i]);
    }
}

// Forma descendientes con parejas distintas y agrega solo los factibles.
void casamiento(vector<vector<int>> &poblacion,
                const vector<vector<int>> &padres,
                const vector<Activo> &activos,
                double presupuesto) {
    for (int i = 0; i < (int)padres.size(); i++) {
        for (int j = 0; j < (int)padres.size(); j++) {
            if (i != j) {
                vector<int> hijo;
                creaHijo(padres[i], padres[j], hijo);
                if (!aberracion(hijo, activos, presupuesto)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Ejecuta las etapas desarrolladas: población, fitness, selección y cruce.
void genetic_algorithm(const vector<Activo> &activos, double presupuesto) {
    vector<vector<int>> poblacion;
    init_population(poblacion, activos, presupuesto);

    vector<double> fitnessPoblacion;
    evaluate_population(poblacion, activos, presupuesto, fitnessPoblacion);

    cout << "\nPOBLACION INICIAL:\n";
    for (int i = 0; i < (int)poblacion.size(); i++) {
        cout << "Individuo " << i + 1 << ": ";
        for (int gen : poblacion[i]) cout << gen << " ";
        cout << " | Fitness: " << fitnessPoblacion[i] << endl;
    }

    vector<vector<int>> padres;
    seleccion(poblacion, fitnessPoblacion, padres);

    cout << "\nPADRES SELECCIONADOS:\n";
    for (int i = 0; i < (int)padres.size(); i++) {
        cout << "Padre " << i + 1 << ": ";
        for (int gen : padres[i]) cout << gen;
        cout << endl;
    }

    int cantidadAntes = (int)poblacion.size();
    casamiento(poblacion, padres, activos, presupuesto);

    cout << "\nHIJOS VALIDOS GENERADOS: "
         << poblacion.size() - cantidadAntes << endl;

    for (int i = cantidadAntes; i < (int)poblacion.size(); i++) {
        cout << "Hijo " << i - cantidadAntes + 1 << ": ";
        for (int gen : poblacion[i]) cout << gen;
        cout << " | Fitness: "
             << calculafitness(poblacion[i], activos, presupuesto)
             << endl;
    }
}

int main() {
    srand((unsigned)time(nullptr));

    vector<Activo> assetPool = {
        {100, 150, 80}, {200, 250, 180}, {150, 220, 130},
        {120, 180, 100}, {180, 230, 160}, {110, 170, 90},
        {130, 200, 110}, {160, 210, 140}, {140, 190, 120},
        {210, 270, 190}, {170, 240, 150}, {190, 260, 170},
        {220, 300, 200}, {200, 280, 180}, {180, 250, 160},
        {195, 260, 175}, {205, 275, 185}, {215, 285, 195},
        {225, 295, 205}, {235, 305, 215}
    };

    double presupuesto = 1000;
    genetic_algorithm(assetPool, presupuesto);
    return 0;
}
