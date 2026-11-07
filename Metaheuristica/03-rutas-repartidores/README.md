# Ruta de reparto con ganancias (2024-2)

## Contexto y enunciado resumido

Un repartidor parte del punto **A** y solo puede moverse entre puntos conectados según una lista de destinos. Visitar cada punto ofrece una ganancia; no se puede volver a visitar un punto.

**Se pide:** construir una ruta factible de máxima ganancia, partiendo de A.

**Objetivo:** `max(suma_de_ganancias_de_los_destinos_visitados)`. **GRASP:** RCL de destinos alcanzables y no visitados que favorece ganancias altas; la construcción termina cuando ya no existe siguiente movimiento. `alfa=0.40`, `iteraciones=10000`.

[Material de práctica de 2024-2](https://drive.google.com/file/d/1mSQb3TPUOajxsFErKONGCja2mWOESyw1/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
