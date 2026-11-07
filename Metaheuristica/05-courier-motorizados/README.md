# Asignación de motorizados a ciudades (práctica 2025-2)

## Contexto y enunciado resumido

Una empresa de mensajería envía paquetes a cuatro ciudades. Para cada ciudad existe un costo fijo de transporte y una tabla de costos de contratación de cinco motorizados.

**Se pide:** elegir un motorizado por ciudad, sin que el costo individual del envío supere **S/ 20**, y **minimizar el costo total**. En este caso de práctica, un mismo motorizado puede atender varias ciudades.

**Objetivo:** `min(suma(costo_transporte + costo_motorizado))`. **GRASP:** una RCL de minimización por ciudad entre los motorizados factibles; se elige aleatoriamente dentro de los costos próximos al menor. `alfa=0.30`, `iteraciones=1000`.

Estos datos son los empleados en la **adaptación de práctica** que desarrollamos; no se afirma que sean una transcripción literal de todos los datos del examen.

[Material 2025-2](https://drive.google.com/file/d/1t7TFKWInjjistb6gUl_2DpahG0U-EsLe/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
