# Resultados Experimentales

## T1 - Validación del makespan

Ejemplo:
- Cmax(1,2,3,4) = 28
- Cmax(3,4,2,1) = 21

La implementación reproduce ambos valores de referencia.

## T2 - Algoritmos de referencia 
Implementados:
- Búsqueda Aleatoria (Random Search)
- NEH

## T3 - Algoritmo Genético
Configuración actualmente en estudio:
- pc = 0.8
- Tamaño de torneo = 3
- N = 50
- pm = 0.1

Operadores:
- Selección por torneo
- Cruce OX
- Mutación por intercambio (Swap)
- Mutación por inserción
- Reemplazo generacional con elitismo

Modificaciones (en ramas distintas): 
- Insertion local search
- Partially Mapped Crossover

## T5 - Ajuste de parámetros
### Configuraciones probadas
Se probaron los siguientes valores de parámetros:

- Tamaño de la población: N = 50, 100
- Probabilidad de mutación: pm = 0.05, 0.10
- Probabilidad de cruzamiento: pc = 0.8
- Tamaño del torneo: 3
- Presupuesto de evaluaciones: 50 000

### Instancia tai20_10_0
| N | pm   | Mean RPD | Best Cmax |
| 50| 0.05 | 3.0721   | 1608      |
| 50| 0.10 | 2.2377   | 1604      |
|100| 0.05 | 2.3704   | 1593      |
|100| 0.10 | 2.9330   | 1614      |
Para esta instancia, N = 50 y pm = 0.10 produjeron el RPD medio más bajo. Aunque N = 100 y pm = 0.05 produjeron la mejor solución individual, su rendimiento promedio a lo largo de las 10 ejecuciones independientes fue ligeramente peor.

### Instancia tai50_5_0
Otra ronda de pruebas, cambiando los siguientes parámetros:

- Tamaño de la población: N = 50
- Probabilidad de mutación: pm = 0.10, 0.30
- Probabilidad de cruzamiento: pc = 0.8, 0.45
- Tamaño del torneo: 3
- Presupuesto de evaluaciones: 50 000

| pc   | pm   | Mean RPD | Std.dev RPD | BestCmax | Mean Cmax |
| 0.80 | 0.10 | 0.5360   | 0.3235      | 2724     | 2738.6    |
| 0.45 | 0.10 | 0.5653   | 0.3741      | 2724     | 2739.4    |
| 0.80 | 0.30 | 0.3157   | 0.2566      | 2724     | 2732.6    |
| 0.45 | 0.30 | 0.4258   | 0.3167      | 2729     | 2735.6    |

Para esta instancia, la configuración pc = 0.8 y pm = 0.3 obtuvo el RPD medio más bajo y la menor variabilidad.

### Instancia tai100_5_0
En la siguiente ronda de pruebas se cambiaron los siguientes parámetros:

- Tamaño de la población: N = 50, 200
- Probabilidad de mutación: pm = 0.30
- Probabilidad de cruzamiento: pc = 0.8
- Tamaño del torneo: 3, 6, 2
- Presupuesto de evaluaciones: 50 000

 N    | Tournament | Mean RPD(UB) | Std. dev. RPD(UB) | Best Cmax | Mean Cmax | Mean CPU (s) |
| 50  | 2          | 0.7391       | 0.3164            | 5506      | 5533.6    | 0.7513       |
| 50  | 3          | **0.0965**   | **0.1197**        | **5493**  | **5498.3**| 0.7393       |
| 50  | 6          | 0.1001       | 0.1848            | **5493**  | 5498.5    | **0.7339**   |
| 200 | 2          | 1.5784       | 0.2733            | 5560      | 5579.7    | 0.7849       |
| 200 | 3          | 0.5462       | 0.1408            | 5505      | 5523.0    | 0.7576       |
| 200 | 6          | 0.1111       | 0.1513            | **5493**  | 5499.1    | 0.7468       |

La mejor configuración general para esta instancia de ajuste fue N = 50 y tamaño de torneo = 3. Obtuvo el RPD medio más bajo y la menor variabilidad de RPD, alcanzando además la cota superior de referencia Cmax = 5493.

El tamaño de torneo 2 funcionó considerablemente peor para ambos tamaños de población. Aumentar la población de 50 a 200 tampoco mejoró el rendimiento promedio bajo el presupuesto fijo de 50 000 evaluaciones.

El tamaño de torneo 6 produjo resultados cercanos al tamaño de torneo 3, especialmente con N = 50, pero el tamaño de torneo 3 logró un RPD medio ligeramente menor y menor variabilidad.

Configuración seleccionada de esta prueba:
- N = 50
- pc = 0.80
- pm = 0.30
- Tamaño del torneo = 3

### Instancia tai100_5_0, prueba final
Parámetro cambiado:
- Tamaño de la población: N = 50
- Probabilidad de mutación: pm = 0.30, 0.40, 0.50
- Probabilidad de cruzamiento: pc = 0.8
- Tamaño del torneo: 3
- Presupuesto de evaluaciones: 50 000

| pm   | Mean RPD | Std. dev. RPD | Best Cmax | Mean Cmax |
| 0.30 | 0.0965   | 0.1197        | 5493      | 5498.3    |
| 0.40 |**0.0674**| **0.0838**    | 5493      | **5496.7**|
| 0.50 | 0.1893   | 0.2443        | 5493      | 5503.4    |

El aumento de la probabilidad de mutación al 40% demostró ofrecer un mejor rendimiento.

### Configuración final
- Tamaño de la población: N = 50
- Probabilidad de cruzamiento: pc = 0.80
- Probabilidad de mutación: pm = 0.40
- Tamaño del torneo: 3
- Presupuesto de evaluaciones: 50 000

### Justificación
La elección se basó en los experimentos de ajuste:

N = 50 superó claramente a N = 200 bajo el presupuesto fijo de evaluaciones.

pc = 0.80 dio un RPD medio mejor que pc = 0.45.

pm = 0.40 obtuvo el RPD medio más bajo y la menor variabilidad en comparación con pm = 0.10, pm = 0.30 y pm = 0.50.

El tamaño de torneo 3 funcionó mejor que el tamaño 2 y ligeramente mejor que el tamaño 6.

## T6 - Experimentos
Con los valores elegidos para los parámetros, se evaluaron 117 instancias, excluyendo las tres instancias utilizadas durante T5 (tai20_10_0, tai50_5_0 y tai100_5_0).
También es importante mencionar que NEH es determinista, por lo que se almacenó una única ejecución por instancia ya que las ejecuciones repetidas producirían el mismo resultado.
El RPD medio obtenido para cada grupo de instancias fue:
n	  m	  GA   RandomSearch  NEH
20	5	  0.8836	5.7172	3.0823
20	10	2.2823	9.3038	4.7974
20	20	1.9710	7.7813	3.6634
50	5	  0.5950	4.7648	0.5276
50	10	3.3485	13.1159	5.0755
50	20	4.6131	15.7745	5.8483
100	5	  0.5537	3.8780	0.3238
100	10	2.1665	10.1060	2.3860
100	20	4.8506	15.1784	4.7119
200	10	1.9458	8.2999	1.2771
200	20	5.0648	14.2670	3.1637
500	20	4.5563	11.0815	1.8762

En todo el conjunto de evaluación completo, el RPD promedio fue de aproximadamente 2.78% para el AG, 3.09% para NEH y 10.04% para Random Search. Por lo tanto, el AG mejora sustancialmente a Random Search y obtiene un resultado general ligeramente mejor que NEH, aunque NEH sigue siendo mejor en varios de los grupos de instancias más grandes.
También se estudió la convergencia en tai100_10_1 y tai500_20_0. El mejor makespan hasta el momento se registró cada 1 000 evaluaciones y se promedió a lo largo de las 10 ejecuciones.
Para tai100_10_1, el AG mejoró de un Cmax medio mejor de 5958.9 a las 1 000 evaluaciones a 5464.6 a las 50 000, mientras que Random Search finalizó en 5980.1. Para tai500_20_0, el AG mejoró de 29057.7 a 27534.1, mientras que Random Search finalizó en 29161.0. Las gráficas de convergencia incluidas en el libro de trabajo experimental muestran que el AG mejora continuamente las soluciones a lo largo de la búsqueda, aunque la tasa de mejora disminuye hacia el final.

## T7 - Análisis
### ¿Qué componente influye más en los resultados?
Los experimentos de ajuste sugieren que el tamaño del torneo y la probabilidad de mutación tienen la mayor influencia en el rendimiento. En particular, el tamaño de torneo 2 funcionó mucho peor que los tamaños 3 y 6, mientras que pm = 0.4 dio mejores resultados promedio y menor variabilidad que pm = 0.3 y pm = 0.5.

Entre los parámetros probados, el tamaño del torneo mostró el mayor cambio en el rendimiento.

### ¿Existe convergencia prematura?
No he encontrado suficientes pruebas (pesadas / fuertes) para concluir que exista una convergencia prematura de forma grande. En ambos experimentos de convergencia, el AG continuó mejorando a lo largo del presupuesto de 50 000 evaluaciones.

Para tai100_10_1, el Cmax medio mejor disminuyó de 5958.9 a las 1 000 evaluaciones a 5464.6 a las 50 000. Para tai500_20_0, disminuyó de 29057.7 a 27534.1.

Sin embargo, las curvas se vuelven más planas cerca del final, especialmente para la instancia más pequeña, lo que indica que la mejora se ralentiza a medida que la población converge. Hay un archivo .xlsx con las gráficas y también los datos brutos recolectados en la carpeta de resultados.

### ¿Cuánto mejora el AG respecto a NEH?
En todo el conjunto de evaluación completo:

RPD medio del AG: aproximadamente 2.78%
RPD medio de NEH: aproximadamente 3.09%
Esto representa una mejora de aproximadamente 0.31 puntos porcentuales, o aproximadamente una reducción relativa del 10% en el RPD.

La mejora no es uniforme: el AG funciona mejor que NEH en 6 de los 12 grupos de instancias, mientras que NEH funciona mejor en los otros 6. El AG funciona particularmente bien en varios grupos pequeños y medianos, mientras que NEH se mantiene más fuerte en algunas de las instancias más grandes.

### Comparación con resultados publicados
Los valores de referencia proporcionados con el trabajo indican que NEH obtiene valores de RPD medio de alrededor del 3%, mientras que los algoritmos genéticos híbridos pueden alcanzar valores por debajo del 1%.

El resultado obtenido de NEH de aproximadamente 3.09% es consistente con esta referencia. El AG alcanza aproximadamente 2.78%, mejorando ligeramente respecto a NEH pero manteniéndose bastante por encima de los resultados de algoritmos genéticos híbridos más avanzados.

Esto indica que el AG implementado es efectivo en comparación con Random Search y competitivo con NEH, pero no obstante hay margen de mejora.