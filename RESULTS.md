# Experimental Results

## T1 - Makespan validation

Example instance:

- Cmax(1,2,3,4) = 28
- Cmax(3,4,2,1) = 21

The implementation reproduces both reference values.

## T2 - Reference algorithms

Implemented:
- Random Search
- NEH

## T3 - Genetic Algorithm

Configuration currently under study:
- pc = 0.8
- tournament size = 3
- N = 50
- pm = 0.1

Operators:
- Tournament selection
- OX crossover
- Swap mutation
- Insertion mutation
- Generational replacement with elitism

## T5 - Parameter tuning

### Configurations tested

The following parameter values were tested:

- Population size: N = 50, 100
- Mutation probability: pm = 0.05, 0.10
- Crossover probability: pc = 0.8
- Tournament size: 3
- Evaluation budget: 50,000

### Instance tai20_10_0

| N | pm | Mean RPD | Best Cmax |
| 50 | 0.05 | 3.0721 | 1608 |
| 50 | 0.10 | 2.2377 | 1604 |
| 100 | 0.05 | 2.3704 | 1593 |
| 100 | 0.10 | 2.9330 | 1614 |

For this instance, N = 50 and pm = 0.10 produced the lowest mean RPD. Although N = 100 and pm = 0.05 produced the best
individual solution, its average performance across the 10
independent runs was slightly worse.

### Instance tai50_5_0
Another testing round, changing the following parameters:

- Population size: N = 50
- Mutation probability: pm = 0.10, 0.30
- Crossover probability: pc = 0.8, 0.45
- Tournament size: 3
- Evaluation budget: 50,000

| pc  | pm | Mean RPD | Std. dev. RPD | Best Cmax |
| 0.80 | 0.10 | 0.5360 | 0.3235 | 2724 | 2738.6 |
| 0.45 | 0.10 | 0.5653 | 0.3741 | 2724 | 2739.4 |
| 0.80 | 0.30 | 0.3157 | 0.2566 | 2724 | 2732.6 |
| 0.45 | 0.30 | 0.4258 | 0.3167 | 2729 | 2735.6 |

For this instance, the configuration pc = 0.8 and pm = 0.3
obtained the lowest mean RPD and the lowest variability.


### Instance tai100_5_0
Next testing round changed the following parameters:

- Population size: N = 50, 200
- Mutation probability: pm = 0.30
- Crossover probability: pc = 0.8
- Tournament size: 3, 6, 2
- Evaluation budget: 50,000

 N | Tournament | Mean RPD(UB) | Std. dev. RPD(UB) | Best Cmax | Mean Cmax | Mean CPU (s) |
|---:|---:|---:|---:|---:|---:|---:|
| 50  | 2 | 0.7391 | 0.3164 | 5506 | 5533.6 | 0.7513 |
| 50  | 3 | **0.0965** | **0.1197** | **5493** | **5498.3** | 0.7393 |
| 50  | 6 | 0.1001 | 0.1848 | **5493** | 5498.5 | **0.7339** |
| 200 | 2 | 1.5784 | 0.2733 | 5560 | 5579.7 | 0.7849 |
| 200 | 3 | 0.5462 | 0.1408 | 5505 | 5523.0 | 0.7576 |
| 200 | 6 | 0.1111 | 0.1513 | **5493** | 5499.1 | 0.7468 |

The best overall configuration for this tuning instance was
N = 50 and tournament size = 3. It obtained the lowest mean
RPD and the lowest RPD variability, while also reaching the
reference upper bound Cmax = 5493.

Tournament size 2 performed considerably worse for both
population sizes. Increasing the population from 50 to 200
also did not improve average performance under the fixed
50,000-evaluation budget.

Tournament size 6 produced results close to tournament size 3,
especially with N = 50, but tournament size 3 achieved a
slightly lower mean RPD and lower variability.

Selected configuration from this test:

- N = 50
- pc = 0.80
- pm = 0.30
- Tournament size = 3

### Instance tai100_5_0, final testing
Parameter changed:
- Population size: N = 50
- Mutation probability: pm = 0.30, 0.40, 0.50
- Crossover probability: pc = 0.8
- Tournament size: 3
- Evaluation budget: 50,000
 pm | Mean RPD | Std. dev. RPD | Best Cmax | Mean Cmax |
| 0.30 | 0.0965 | 0.1197 | 5493 | 5498.3 |
| 0.40 | **0.0674** | **0.0838** | **5493** | **5496.7** |
| 0.50 | 0.1893 | 0.2443 | **5493** | 5503.4 |

The mutation probability rising to 40% proved to be have better performance

### Final configuration

- Population size: N = 50
- Crossover probabilitry: pc = 0.80
- Mutation probability: pm = 0.40
- Tournament sizd : 3
- Evaluation budget: 50,000

### Justification

The choice was based on the tuning experiments:
- N = 50 clearly outperformed N = 200 under the fixed evaluation budget.
- pc = 0.80 gave better mean RPD than pc = 0.45.
- pm = 0.40 obtained the lowest mean RPD and lowest variability compared with pm = 0.10, pm = 0.30 and pm = 0.50.
- Tournament size 3 performed better than size 2 and slightly better than size 6.


## T6 - Experiments
With the chosen values for the parameters, 117 instances were evaluated, excluding the three instances used during T5 (tai20_10_0, tai50_5_0 and tai100_5_0)
It's also important to mention that NEH is deterministic, so a single execution per instance was stored because repeated executions would produce the same result. 
The mean RPD obtained for each instance group was:
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

Across the complete evaluation set, the average RPD was approximately 2.78% for the GA, 3.09% for NEH, and 10.04% for Random Search. Therefore, the GA substantially improves on Random Search and obtains a slightly better overall result than NEH, although NEH remains better on several of the larger instance groups.
Convergence was also studied on tai100_10_1 and tai500_20_0. The best-so-far makespan was recorded every 1,000 evaluations and averaged across the 10 runs.
For tai100_10_1, the GA improved from a mean best Cmax of 5958.9 at 1,000 evaluations to 5464.6 at 50,000, while Random Search finished at 5980.1. For tai500_20_0, the GA improved from 29057.7 to 27534.1, whereas Random Search finished at 29161.0. The convergence graphs included in the experimental workbook show that the GA continuously improves solutions throughout the search, although the rate of improvement decreases toward the end.

## T7 - Analysis

### Which component influences results most?


The tuning experiments suggest that **tournament size and mutation probability** have the strongest influence on performance. In particular, tournament size 2 performed much worse than sizes 3 and 6, while pm = 0.4 gave better average results and lower variability than pm = 0.3 and pm = 0.5.

Among the tested parameters, tournament size showed the largest performance change.

### Is there premature convergence?

I have not found enough evidence to conclude that there is severe premature convergence. In both convergence experiments, the GA continued improving throughout the 50,000-evaluation budget.

For tai100_10_1, the mean best Cmax decreased from 5958.9 at 1,000 evaluations to 5464.6 at 50,000. For tai500_20_0, it decreased from 29057.7 to 27534.1.

However, the curves become flatter near the end, especially for the smaller instance, indicating that improvement slows as the population converges. There is an .xlxs file with the graphs, and also the raw collected data in the results folder.

### How much does GA improve over NEH?
Across the complete evaluation set:

- GA mean RPD: approximately **2.78%**
- NEH mean RPD: approximately **3.09%**

This represents an improvement of about **0.31 percentage points**, or roughly a **10% relative reduction in RPD**.

The improvement is not uniform: GA performs better than NEH in 6 of the 12 instance groups, while NEH performs better in the other 6. The GA performs particularly well on several small and medium groups, while NEH remains stronger on some of the largest instances.

### Comparison with published results

The reference values provided with the assignment indicate that NEH obtains mean RPD values of around **3%**, while hybrid genetic algorithms can achieve values below **1%**.

The obtained NEH result of approximately **3.09%** is consistent with this reference. The GA achieves approximately **2.78%**, improving slightly over NEH but remaining well above the results of more advanced hybrid genetic algorithms.

This indicates that the implemented GA is effective compared with Random Search and competitive with NEH, but there is however room for improvement.