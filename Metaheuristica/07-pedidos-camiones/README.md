# Distribución de pedidos en camiones (práctica 2026-1)

## Contexto y enunciado resumido

Seis pedidos con distintos pesos deben transportarse mediante camiones de capacidad **50 kg** cada uno.

**Se pide:** asignar todos los pedidos sin superar el límite de carga de ningún camión y **minimizar la cantidad de camiones**.

**Objetivo:** `min(numero_de_camiones)`. **GRASP:** llenar un camión con una RCL de pedidos pendientes que aún caben, priorizando pesos mayores. Cuando no entra ningún pedido adicional, iniciar otro camión. `alfa=0.20`, `iteraciones=1000`.

[Material de práctica 2026-1](https://drive.google.com/file/d/1VXktCbE8fVOpm1HVTrDCWPb7MOsTkK55/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
