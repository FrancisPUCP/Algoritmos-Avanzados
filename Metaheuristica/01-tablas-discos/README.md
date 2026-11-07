# Tablas y discos (2024-1, pregunta 1)

## Contexto y enunciado resumido

Un administrador de bases de datos debe distribuir seis tablas entre tres discos. Cada tabla exige almacenamiento (GB) y rendimiento (IOPS). Cada disco pierde recursos cuando recibe una tabla.

**Se pide:** asignar todas las tablas sin exceder capacidad ni velocidad de los discos, buscando que el disco *más lento al terminar* conserve la mayor velocidad posible.

**Objetivo:** `max(min(IOPS_libres_de_cada_disco))`. **GRASP:** RCL de tablas pendientes con mayor demanda de IOPS (maximización); asignación determinista al disco factible con mayor rendimiento restante. `alfa=0.30`, `iteraciones=10000` (el enunciado muestra ejemplos con 10 000 y 100 000). **Referencia:** velocidad mínima de 40 IOPS.

[Enunciado original](https://drive.google.com/file/d/1nPwHVwUjE1TWgrRqQkXEVJ_yju2kPe19/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
