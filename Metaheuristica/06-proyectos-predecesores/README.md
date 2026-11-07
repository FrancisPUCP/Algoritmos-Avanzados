# Selección de proyectos con precedencias (práctica 2026-1)

## Contexto y enunciado resumido

Una organización debe elegir proyectos con **presupuesto máximo de 400**. Cada proyecto tiene costo, ganancia y, en algunos casos, predecesores obligatorios.

**Se pide:** seleccionar proyectos que respeten el presupuesto y todas las dependencias, **maximizando la ganancia total**.

**Objetivo:** `max(suma_de_ganancias)`. **GRASP:** la RCL considera únicamente proyectos cuyo costo cabe y cuyos predecesores ya fueron seleccionados. El mérito heurístico combina la ganancia del proyecto con la de sus sucesores directos para favorecer decisiones que desbloqueen más opciones. El mérito es distinto de la función objetivo. `alfa=0.30`, `iteraciones=1000`.

[Material de práctica 2026-1](https://drive.google.com/file/d/1VXktCbE8fVOpm1HVTrDCWPb7MOsTkK55/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
