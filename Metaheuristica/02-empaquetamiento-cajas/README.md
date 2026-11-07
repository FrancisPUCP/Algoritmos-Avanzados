# Empaquetamiento de objetos en cajas (2024-2)

## Contexto y enunciado resumido

Se tienen seis objetos identificados por letras, con pesos distintos, y cajas de capacidad máxima de 10 kg.

**Se pide:** acomodar todos los objetos sin superar la capacidad por caja y **minimizar el número de cajas**.

**Objetivo:** `min(cantidad_de_cajas)`. **GRASP:** dentro de cada caja, candidatos no usados que caben; RCL que privilegia los objetos de mayor peso. Al agotarse los candidatos se abre otra caja. `alfa=0.30`, `iteraciones=1000` son los parámetros de práctica utilizados.

[Material de práctica de 2024-2](https://drive.google.com/file/d/1mSQb3TPUOajxsFErKONGCja2mWOESyw1/view)

## Compilación y ejecución

Desde la raíz del repositorio, usa `g++ -std=c++17 -O2 <ruta-al-main.cpp> -o programa` y después ejecuta `./programa` (Windows: `programa.exe`). También puedes utilizar el `CMakeLists.txt` del repositorio.

## Nota didáctica

La construcción GRASP es aleatorizada: encontrar un valor en una ejecución no implica que todas las ejecuciones ni todas las heurísticas encuentren el óptimo. Los programas fijan una semilla para reproducir las pruebas.
