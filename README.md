# PFSP - Algoritmo Genético
# Autor: Pablo Jesús Moreda Vega
# alu: alu0101848297

Implementación en C++ de distintos métodos para resolver el Permutation Flow Shop Scheduling Problem (PFSP).

# Configuración final del GA

Tras el ajuste experimental de parámetros se seleccionó:

Population size (N): 50
Crossover probability (pc): 0.8
Mutation probability (pm): 0.4
Tournament size: 3
Evaluation budget: 50,000


Las ejecuciones experimentales utilizan las semillas:

42, 43, ..., 51


# 4. Estructura del proyecto

GenAlg/
├── Makefile
├── README.md
├── instances/
│   ├── tai20_5_0.fsp
│   ├── tai20_5_1.fsp
│   ├── ...
│   └── tai500_20_9.fsp
│
├── results/
│   ├── t5_results.csv
│   ├── t6_results.csv
│   ├── instance_summary.csv
│   ├── group_summary.csv
│   ├── convergence.csv
│   └── convergence_summary.csv
│
├── src/
│   ├── main.cpp
│   ├── instance.cpp
│   ├── instance.h
│   ├── instance_reader.cpp
│   ├── instance_reader.h
│   ├── genetic_algorithm.cpp
│   ├── genetic_algorithm.h
│   ├── random_search.cpp
│   ├── random_search.h
│   ├── neh.cpp
│   ├── neh.h
│   ├── metrics.cpp
│   ├── metrics.h
│   ├── experiments.cpp
│   └── experiments.h
│
└── build/


build/ se genera automáticamente durante la compilación.

El ejecutable generado es:
pfsp

# Compilación

Desde el directorio raíz del proyecto (terminal):
make

Esto genera:
./pfsp

Para eliminar los archivos compilados:
make clean


# Ejecución normal

## Parámetros por defecto

Sintaxis:
./pfsp <input_file> <seed>

Ejemplo:
./pfsp instances/tai20_5_0.fsp 42

Se utilizan automáticamente:
N = 50
pc = 0.8
pm = 0.4
tournament = 3
evaluations = 50,000

El programa muestra:

- Mejor makespan.
- Mejor permutación.
- Número de trabajos.
- Número de máquinas.
- UB.
- RPD.


# Ejecución con parámetros personalizados

Sintaxis:
./pfsp <input_file> <seed> <population> <pc> <pm> <tournament>

Ejemplo:

./pfsp instances/tai100_5_0.fsp 42 50 0.8 0.4 3

Los parámetros son:

population  Tamaño de la población
pc          Probabilidad de crossover
pm          Probabilidad de mutación
tournament  Tamaño del torneo
seed        Semilla del generador pseudoaleatorio

Ejemplo para realizar una prueba con mayor población:
./pfsp instances/tai100_5_0.fsp 42 200 0.8 0.4 3



# Modo experimental de una instancia

Para realizar 10 ejecuciones independientes sobre una instancia:

./pfsp -e <input_file>

Ejemplo:
./pfsp -e instances/tai20_5_0.fsp

Las semillas utilizadas son: 42 - 51


También pueden indicarse parámetros personalizados:
./pfsp -e <input_file> <population> <pc> <pm> <tournament>

Ejemplo:

./pfsp -e instances/tai100_5_0.fsp 50 0.8 0.4 3

Los resultados se almacenan en:

raw_results.csv

Para cada instancia se ejecutan:

10 ejecuciones GA
10 ejecuciones Random Search
1 ejecución NEH

NEH solo necesita una ejecución porque es determinista.


# Formato de raw_results.csv

El fichero contiene:

Instance
n
m
Algorithm
Run
Seed
Population
pc
pm
Tournament
Cmax
CPU
RPD(UB)

Ejemplo:

Instance,n,m,Algorithm,Run,Seed,Population,pc,pm,Tournament,Cmax,CPU,RPD(UB)
instances/tai20_5_0.fsp,20,5,GA,1,42,50,0.8,0.4,3,1278,0.05,0

# Reset de resultados

Para eliminar el fichero experimental actual:
./pfsp -r

Esto elimina raw_results.csv


# Ejecución de un grupo completo

Sintaxis:
./pfsp -g <jobs> <machines>

Ejemplo:
./pfsp -g 20 5

Ejecuta automáticamente:
tai20_5_0.fsp
tai20_5_1.fsp
...
tai20_5_9.fsp

Cada instancia genera las ejecuciones correspondientes de GA,
Random Search y NEH.




# Ajuste de parámetros - T5 (VER EN RESULTADOS.md)

Durante el ajuste de parámetros se utilizaron instancias distintas
del conjunto de evaluación final.

Se estudiaron diferentes valores de:

Population size:
N = 50, 200

Crossover:
pc = 0.45, 0.80

Mutation:
pm = 0.10, 0.30, 0.40, 0.50

Tournament:
2, 3, 6

Los principales resultados mostraron que:

- N = 50 obtuvo mejores resultados que N = 200 bajo el presupuesto fijo de 50.000 evaluaciones.
- pc = 0.8 obtuvo mejores resultados que pc = 0.45.
- pm = 0.4 obtuvo el mejor equilibrio entre calidad y variabilidad.
- Un torneo de tamaño 2 produjo resultados claramente peores.
- Los tamaños 3 y 6 fueron similares, pero tamaño 3 obtuvo ligeramente
  mejores resultados medios.

La configuración final seleccionada fue:
N = 50
pc = 0.8
pm = 0.4
Tournament = 3

Las instancias empleadas para tuning fueron:
tai20_10_0.fsp
tai50_5_0.fsp
tai100_5_0.fsp

Estas instancias se excluyeron posteriormente del conjunto final de
evaluación.

# Experimentación final - T6 (VER EN RESULTADOS.md)

La configuración definitiva se ejecutó sobre las instancias de
evaluación utilizando:

10 ejecuciones independientes
50,000 evaluaciones por ejecución
Semillas 42 - 51

Los resultados originales se almacenan en:
results/t6_results.csv


## Generar las tablas T6

Para procesar automáticamente los resultados:
./pfsp -s results/t6_results.csv

Se generan:
results/instance_summary.csv
results/group_summary.csv

## Tabla por instancia

instance_summary.csv contiene:
Instance
n
m
BestCmax
StdDevCmax
NEHCmax
MeanCPU
MeanRPD(UB)
StdDevRPD(UB)
RPD(NEH)

BestCmax representa el mejor resultado del GA entre las 10 ejecuciones.

StdDevCmax representa la desviación típica del makespan del GA.

MeanCPU representa el tiempo medio de ejecución.

MeanRPD(UB) representa el RPD medio de las 10 ejecuciones.

RPD(NEH) compara el mejor resultado del GA con el resultado de NEH.

Un valor negativo de RPD(NEH) indica que el mejor resultado del GA mejora el resultado obtenido por
NEH.

## Tabla por grupo

`group_summary.csv` contiene:

n
m
Algorithm
MeanRPD(UB)

y proporciona el RPD medio para cada grupo n × m y
algoritmo.

Resultados obtenidos:

| n   | m  | GA     | RandomS | NEH    |
| 20  | 5  | 0.8836 | 5.7172  | 3.0823 |
| 20  | 10 | 2.2823 | 9.3038  | 4.7974 |
| 20  | 20 | 1.9710 | 7.7813  | 3.6634 |
| 50  | 5  | 0.5950 | 4.7648  | 0.5276 |
| 50  | 10 | 3.3485 | 13.1159 | 5.0755 |
| 50  | 20 | 4.6131 | 15.7745 | 5.8483 |
| 100 | 5  | 0.5537 | 3.8780  | 0.3238 |
| 100 | 10 | 2.1665 | 10.1060 | 2.3860 |
| 100 | 20 | 4.8506 | 15.1784 | 4.7119 |
| 200 | 10 | 1.9458 | 8.2999  | 1.2771 |
| 200 | 20 | 5.0648 | 14.2670 | 3.1637 |
| 500 | 20 | 4.5563 | 11.0815 | 1.8762 |

Aproximadamente:
GA            ≈ 2.78 % RPD
NEH           ≈ 3.09 % RPD
Random Search ≈ 10.04 % RPD



## Generar datos de convergencia
./pfsp -c <input_file>

Ejemplo:
./pfsp -c instances/tai100_10_1.fsp

Los resultados se almacenan en results/convergence.csv

Para cada punto se almacena:
Instance
n
m
Algorithm
Run
Seed
Evaluation
BestCmax

Estos valores proceden directamente del estado real del algoritmo
durante las ejecuciones.


## Generar resumen de convergencia
./pfsp -cs results/convergence.csv

Esto genera:
results/convergence_summary.csv

El fichero contiene:
Instance
n
m
Algorithm
Evaluation
MeanBestCmax
StdDevBestCmax

El valor MeanBestCmax corresponde a la media del mejor makespan encontrado entre las 10 ejecuciones en ese punto de evaluación.


## Gráficas de convergencia

Para construir las gráficas se utiliza:
Eje X:
Número de evaluaciones

Eje Y:
MeanBestCmax

Se comparan GA y Random Search

Las dos instancias utilizadas para las gráficas finales son:
tai100_10_1.fsp
tai500_20_0.fsp

# 28. Comandos disponibles

Resumen:
## Compilar
make

## Limpiar compilación
make clean

## GA con configuración por defecto
./pfsp <instance> <seed>

## GA con configuración personalizada
./pfsp <instance> <seed> <N> <pc> <pm> <tournament>

## Experimento de una instancia
./pfsp -e <instance>

## Experimento personalizado
./pfsp -e <instance> <N> <pc> <pm> <tournament>

## Grupo
./pfsp -g <jobs> <machines>

## Grupo excluyendo una instancia
./pfsp -g <jobs> <machines> <skip_index>

## Eliminar raw_results.csv
./pfsp -r

## Experimento de convergencia
./pfsp -c <instance>

## Generar tablas T6
./pfsp -s results/t6_results.csv

## Generar resumen de convergencia
./pfsp -cs results/convergence.csv