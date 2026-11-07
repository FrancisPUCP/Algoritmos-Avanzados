# Asignación de órdenes a líneas de embotellado (2025-1, pregunta 3)

## Contexto y enunciado resumido

Una planta debe distribuir **20 órdenes** entre **5 líneas paralelas** de producción. Para el modelo simplificado del ejercicio cada botella representa **6 minutos** de trabajo en su línea. Todas las órdenes deben procesarse.

**Se pide:** minimizar el **makespan**, es decir, el mayor tiempo acumulado entre las cinco líneas (no la suma de todos los tiempos).

**Parte A:** la RCL prioriza órdenes con **mayor cantidad de botellas**. **Parte B:** la selección respeta primero la **prioridad** (se asume que 1 es la más alta) y desempata por cantidad de botellas; se utiliza una sola RCL, filtrando primero por prioridad. En ambos casos se asigna la orden elegida a la línea actualmente menos cargada.

**Objetivo:** `min(max(tiempo_acumulado_linea))`. `alfa=0.30` e `iteraciones=1000` **son parámetros de práctica, no requisitos explícitos del PDF**. El ejemplo del profesor muestra 2724 minutos; la cota inferior de estos datos es 2688 minutos.

- `parte-a/main.cpp`: sin prioridad.
- `parte-b/main.cpp`: prioridad estricta, luego botellas.

[Enunciado original](https://drive.google.com/file/d/1uudRAFLVXJl3B2IS4byBTH3PSW9mtO5q/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
