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

Pending.

## T7 - Analysis

### Which component influences results most?

Pending.

### Is there premature convergence?

Pending.

### How much does GA improve over NEH?

Pending.

### Comparison with published results

Pending.