# Selección y depuración del ZIP original

El ZIP contenía **10 proyectos de CLion** (con numerosos archivos intermedios de compilación). Se organizaron en **7 temas** y **8 programas autónomos**:

| Origen dentro del ZIP | Versión publicada | Decisión |
|---|---|---|
| `Problema1-TablasYDiscos` y `Problema9` | `01-tablas-discos` | Dos soluciones del mismo problema; se publica una sola versión funcional comentada. |
| `Problema2-PedidosYCamiones` | `07-pedidos-camiones` | Único problema, completado y mejorado: imprime la mejor distribución, elimina TODO residuales y evita ciclos imposibles. |
| `Problema3-ProyectosConPredecesores` | `06-proyectos-predecesores` | Conservado, documentado y limpiado. |
| `Problema4-EmpaquetamientosEnCajas` | `02-empaquetamiento-cajas` | Conservado, documentado y con comprobaciones de factibilidad. |
| `Problema5-GananciasRepartidores` | `03-rutas-repartidores` | Conservado y documentado. |
| `Problema7` | `04-produccion-botellas/parte-a` | Versión completa para ordenar por cantidad de botellas. |
| `Problema7v2` | `04-produccion-botellas/parte-b` | Variante distinta del mismo enunciado: prioridad, luego cantidad. |
| `Problema7_PlanificaciónOrdenesProduccion` | *No publicada* | Versión preliminar con errores de la RCL y falta de `return`. |
| `Problema8` | `05-courier-motorizados` | Conservado, documentado y con manejo del caso imposible. |

No se incluyen `.idea/`, `cmake-build-debug/`, binarios ni archivos del IDE. Los textos son resúmenes didácticos: no sustituyen el enunciado oficial. Las correcciones buscan mantener el esquema original de **GRASP construcción**, sin añadir búsqueda local.
