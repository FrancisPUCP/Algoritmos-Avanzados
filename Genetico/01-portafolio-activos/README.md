# Portafolio de activos

## Contexto y enunciado resumido

Se dispone de un conjunto de activos financieros. Para cada activo se conoce su precio actual, un precio futuro optimista y un precio futuro pesimista. Se debe decidir cuáles comprar sin superar el presupuesto de inversión.

**Se pide:** representar las decisiones de compra mediante un cromosoma binario, evaluar los portafolios y aplicar las etapas del algoritmo genético desarrolladas en la práctica.

## Representación cromosómica

El cromosoma tiene un gen por activo:

- **1:** se compra el activo.
- **0:** no se compra.

En el programa se consideran 20 activos, por lo que cada individuo tiene 20 genes.

## Restricciones

1. El cromosoma debe tener la misma cantidad de genes que activos.
2. Cada gen debe ser 0 o 1.
3. La suma de los precios actuales de los activos seleccionados no debe superar el presupuesto de 1 000 unidades monetarias indicado en los datos del programa.

## Función fitness

Para los activos seleccionados se calculan las sumas de precios actuales, optimistas y pesimistas. El fitness implementado es:

~~~text
fitness = |suma_optimista - suma_actual| - |suma_pesimista - suma_actual|
~~~

Se busca maximizar este valor: favorece el potencial de subida y descuenta el impacto del escenario pesimista.

## Etapas implementadas

- Población inicial de **NUMIND = 10** individuos; se generan cromosomas binarios y se conservan los que cumplen el presupuesto.
- Evaluación del fitness de cada individuo.
- Selección por ruleta del **TSELECCION = 0.50** de la población.
- **Cruce uniforme:** para cada gen, se elige aleatoriamente si se hereda del padre o de la madre.
- Validación de los hijos antes de agregarlos a la población.

En esta solución no se define PCRUCE: el operador de cruce se aplica a las parejas de padres distintas que recorre la función casamiento. Tampoco se implementan mutación ni múltiples generaciones.

## Archivos

- **main.cpp:** solución completa y comentada en C++.

## Compilación

~~~bash
g++ -std=c++17 -O2 main.cpp -o portafolio
./portafolio
~~~
