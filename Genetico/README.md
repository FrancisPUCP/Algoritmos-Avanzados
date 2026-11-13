# Algoritmos Genéticos

Colección de ejercicios resueltos en C++ durante el repaso de **Algoritmos Avanzados**. Los problemas utilizan cromosomas binarios, evaluación mediante una función fitness, selección por ruleta y operadores de cruce.

## Índice

| Carpeta | Problema | Objetivo |
|---|---|---|
| [01-portafolio-activos](01-portafolio-activos/) | Selección de activos para invertir | Maximizar el fitness del portafolio sin superar el presupuesto |
| [02-asignacion-tareas-empleados](02-asignacion-tareas-empleados/) | Asignación de cinco tareas a cinco empleados | Maximizar la ganancia total respetando una asignación uno a uno |

## Estructura general aplicada

1. **Representación:** definir qué significa cada gen y cómo se forma un cromosoma.
2. **Validación:** comprobar las restricciones del problema.
3. **Fitness:** medir la calidad de cada individuo.
4. **Población inicial:** generar individuos y conservar los factibles.
5. **Evaluación:** calcular el fitness de la población.
6. **Selección:** escoger padres mediante ruleta.
7. **Cruce:** crear descendientes con el operador indicado para cada ejercicio.
8. **Validación de descendientes:** incorporar únicamente los hijos factibles.

## Parámetros que aparecen en los ejercicios

- **NUMIND:** cantidad de individuos de la población inicial.
- **TSELECCION:** proporción de la población que se selecciona como padres.
- **PCRUCE:** probabilidad de ejecutar el cruce para una pareja, cuando el ejercicio la utiliza.
- **PCORTE:** proporción del cromosoma que determina el punto de corte en el cruce de un punto.

No todos los ejercicios utilizan todos los parámetros. En particular, el portafolio utiliza cruce uniforme y no define PCRUCE ni PCORTE.

## Compilación

Cada problema es independiente. Desde la raíz del repositorio puedes compilarlo con:

~~~bash
g++ -std=c++17 -O2 Genetico/01-portafolio-activos/main.cpp -o portafolio
./portafolio

g++ -std=c++17 -O2 Genetico/02-asignacion-tareas-empleados/main.cpp -o asignacion
./asignacion
~~~

Los programas usan aleatoriedad, por lo que la población y los descendientes pueden cambiar entre ejecuciones.

## Alcance de estas soluciones

Se documentan las etapas que se trabajaron para cada ejercicio. Estas versiones muestran una ejecución de generación, evaluación, selección y cruce; **no implementan un ciclo de múltiples generaciones ni mutación**, porque esas etapas no forman parte de las soluciones desarrolladas aquí.

Los contextos de los README individuales son resúmenes didácticos de los ejercicios trabajados, no transcripciones oficiales de los enunciados.
