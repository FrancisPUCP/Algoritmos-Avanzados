# Asignación de tareas a empleados

## Contexto y enunciado resumido

Se tienen cinco tareas y cinco empleados. Una matriz contiene la ganancia obtenida al asignar cada empleado a cada tarea. Se busca encontrar una asignación que maximice la ganancia total.

**Se pide:** asignar exactamente un empleado a cada tarea y, simultáneamente, asignar exactamente una tarea a cada empleado.

## Representación cromosómica

La solución se representa mediante una matriz binaria de 5 × 5, almacenada como un vector de 25 genes en orden por filas.

El gen correspondiente a la tarea i y al empleado j se encuentra en:

~~~cpp
indice = i * n + j;
~~~

- **1:** el empleado j realiza la tarea i.
- **0:** esa asignación no se realiza.

## Restricciones

1. Cada fila debe contener exactamente un 1: cada tarea tiene un único empleado.
2. Cada columna debe contener exactamente un 1: cada empleado recibe una única tarea.

La función aberracion() devuelve true cuando alguna de estas condiciones no se cumple.

## Función fitness

Se suman las ganancias de las asignaciones seleccionadas:

~~~text
fitness = suma(ganancia[i][j] * gen[i][j])
~~~

El objetivo es maximizar la ganancia total.

## Etapas implementadas

- Población inicial de **NUMIND = 20** individuos. Para cada tarea se elige aleatoriamente un empleado; después se descartan las asignaciones que no cumplen la condición uno a uno.
- Evaluación de la ganancia total de cada individuo.
- Selección por ruleta del **TSELECCION = 0.50** de la población.
- Probabilidad de cruce **PCRUCE = 0.80** para cada pareja de padres.
- **Cruce de un punto:** **PCORTE = 0.50** determina el punto de corte. Los genes anteriores al corte provienen del primer padre y los restantes de la madre. Se generan dos hijos intercambiando el orden de los padres.
- Validación de cada hijo; solo se agrega a la población si mantiene una asignación válida.

No se implementan mutación ni un ciclo de múltiples generaciones en esta solución.

## Archivos

- **main.cpp:** solución completa y comentada en C++.

## Compilación

~~~bash
g++ -std=c++17 -O2 main.cpp -o asignacion
./asignacion
~~~
