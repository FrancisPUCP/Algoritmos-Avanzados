# Algoritmos Avanzados — Metaheurísticas GRASP en C++

Colección depurada de **7 problemas y 8 soluciones completas**, resueltos durante la práctica de **Algoritmos Avanzados (PUCP)**. Cada carpeta incluye un `main.cpp` comentado y un `README.md` con **contexto, qué se pide, restricciones, criterio voraz, RCL y función objetivo**.

## Índice de problemas

| Carpeta | Problema | Objetivo | Fuente o práctica |
|---|---|---|---|
| [01-tablas-discos](01-tablas-discos/) | Asignar tablas a discos | Maximizar el mínimo IOPS restante | 2024-1 |
| [02-empaquetamiento-cajas](02-empaquetamiento-cajas/) | Objetos en cajas de 10 kg | Minimizar número de cajas | 2024-2 |
| [03-rutas-repartidores](03-rutas-repartidores/) | Ruta con ganancias y conexiones | Maximizar ganancias | 2024-2 |
| [04-produccion-botellas](04-produccion-botellas/) | Órdenes en cinco líneas: partes A y B | Minimizar makespan | 2025-1 |
| [05-courier-motorizados](05-courier-motorizados/) | Asignar motorizados a ciudades | Minimizar costo total | Práctica 2025-2 |
| [06-proyectos-predecesores](06-proyectos-predecesores/) | Seleccionar proyectos con dependencias | Maximizar ganancia | Práctica 2026-1 |
| [07-pedidos-camiones](07-pedidos-camiones/) | Empaquetar pedidos en camiones | Minimizar número de camiones | Práctica 2026-1 |

## ¿Qué es GRASP construcción?

GRASP (*Greedy Randomized Adaptive Search Procedure*) construye soluciones usando elecciones voraces parcialmente aleatorizadas. En estos programas se desarrolla la **fase constructiva** y se realizan múltiples construcciones independientes; **no se implementa una fase de búsqueda local**.

En general, cada solución sigue estos pasos:

1. Identificar los candidatos **factibles**.
2. Medir su **mérito voraz** (puede ser distinto del objetivo global).
3. Construir una **RCL** (*Restricted Candidate List*) usando un umbral parametrizado por `alfa`.
4. Elegir aleatoriamente un elemento de la RCL y actualizar la solución parcial.
5. Repetir hasta completar la construcción y comparar la solución con la mejor obtenida hasta entonces.

### Umbrales utilizados

Si `mejor` y `peor` se calculan sobre candidatos factibles:

- **Maximización del mérito:** `umbral = mejor - alfa * (mejor - peor)`, admitir `merito >= umbral`.
- **Minimización del mérito:** `umbral = mejor + alfa * (peor - mejor)`, admitir `merito <= umbral`.

`alfa = 0` es completamente voraz; `alfa = 1` admite todos los candidatos factibles. La comparación final siempre usa la **función objetivo del problema** (cantidad de cajas, ganancia total, makespan, mínimo de IOPS, etc.).

## Compilación

**Opción CMake (recomendada)**

```bash
cmake -S . -B build
cmake --build build
```

Los ocho ejecutables se generan en `build/` (la ubicación exacta depende del generador y del sistema operativo).

**Opción g++ por problema**

```bash
g++ -std=c++17 -O2 01-tablas-discos/main.cpp -o tablas_discos
./tablas_discos
```

Puedes sustituir la ruta por la de cualquier otra solución. En Windows usa el `.exe` correspondiente.


## Resultados verificados

Los **8 ejecutables fueron compilados** con `g++ -std=c++17 -O2 -Wall -Wextra -pedantic` y ejecutados con semilla fija `42`. Estos son los mejores valores reportados por los programas con los datos incluidos:

| Programa | Mejor valor obtenido |
|---|---:|
| Tablas y discos | **40 IOPS** de velocidad mínima |
| Objetos en cajas | **2 cajas** |
| Ruta de repartidores | **110** de ganancia |
| Producción, parte A | **2688 minutos** de makespan |
| Producción, parte B | **2916 minutos** de makespan |
| Courier y motorizados | **S/ 70** de costo total |
| Proyectos con precedencias | **1900** de ganancia |
| Pedidos en camiones | **3 camiones** |

La diferencia de resultado entre las partes A y B de producción corresponde a estrategias de construcción distintas. Los números no deben confundirse con una garantía general de optimalidad de GRASP.

## Curaduría del archivo original

Se revisó el ZIP original y se seleccionaron soluciones completas, evitando subir carpetas `.idea`, archivos `cmake-build-debug`, ejecutables `.exe`, objetos `.obj` y versiones preliminares. En **tablas/discos** se conserva una única solución; en **producción** se conservan **dos programas diferentes** porque resuelven las partes A y B del enunciado. Se corrigieron cabeceras, errores de índices y comprobaciones de factibilidad, y se agregaron comentarios y documentación.

## Sobre las fuentes

Los archivos son **soluciones de práctica propias** con enunciados **resumidos y parafraseados**; no se reproducen los PDFs de examen ni se presenta el material como oficial. Los README de cada problema incluyen enlaces a los materiales utilizados cuando estaban disponibles. Los parámetros y supuestos adoptados para practicar se identifican por separado.
