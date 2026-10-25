# Genetic Algorithm for the Permutation Flow Shop Scheduling Problem

A C++17 implementation and experimental study of a **genetic algorithm (GA)** for the **Permutation Flow Shop Scheduling Problem (PFSP)**. The project compares evolutionary search against **Random Search** and the constructive **NEH heuristic**, with reproducible parameter tuning, benchmark runs, and convergence tracking.

The main objective is to minimize the **makespan** (`Cmax`): the completion time of the final job on the final machine. Every machine processes the jobs in the same order, represented by a permutation.

## Highlights

- Permutation-based genetic algorithm with tournament selection, Order Crossover (OX), swap/insertion mutation, and generational replacement with elitism.
- Random Search and NEH baselines for comparison.
- Configurable population size, crossover/mutation probabilities, tournament size, and random seed.
- Fixed budget of **50,000 makespan evaluations** per stochastic run.
- Experimental study across **117 Taillard benchmark instances**, with **10 independent runs** of each stochastic algorithm per instance.
- CSV exports for instance-level statistics, grouped comparisons, and best-so-far convergence.
- Separate experimental branches (`mod1`, `mod2`) for local-search and crossover variants; these are **not part of the main-branch GA**.

## The Problem

For `n` jobs and `m` machines, a solution is a permutation of the jobs. All jobs visit the machines in the same order, and each machine processes jobs according to that permutation. A feasible schedule seeks to minimize:

\[
C_{max} = C_{n,m}
\]

where `C_{n,m}` is the completion time of the last scheduled job on the last machine.

The project reads benchmark instances from `instances/` and evaluates permutations using the processing-time matrix.

## Genetic Algorithm

| Stage | Implementation |
| --- | --- |
| Representation | Permutation of job identifiers |
| Initial population | Randomly shuffled valid permutations |
| Parent selection | Tournament selection |
| Crossover | Order Crossover (OX) |
| Mutation | Randomly chosen swap or insertion mutation |
| Replacement | Generational, preserving the best previous individual when it improves the new generation's worst |
| Stopping criterion | Makespan-evaluation budget |
| Tracking | Best-so-far makespan recorded every 1,000 evaluations |

Each offspring is checked to ensure that every job appears exactly once. When crossover or mutation is not applied, the corresponding parent or child is retained.

The final parameters were selected from an experimental tuning study on **three instances reserved for tuning**:

| Parameter | Selected value |
| --- | ---: |
| Population size (`N`) | 50 |
| Crossover probability (`pc`) | 0.80 |
| Mutation probability (`pm`) | 0.40 |
| Tournament size | 3 |
| Evaluations per run | 50,000 |
| Seeds | 42–51 |

The tuning instances were `tai20_10_0.fsp`, `tai50_5_0.fsp`, and `tai100_5_0.fsp`; these were excluded from the final 117-instance evaluation set.

## Results

The final experiment compared GA and Random Search over 10 independent runs per instance. NEH is deterministic and was evaluated once per instance.

**Mean relative percentage deviation (RPD) from the reference upper bound** across the final evaluation set:

| Algorithm | Mean RPD ↓ |
| --- | ---: |
| **Genetic Algorithm** | **2.78%** |
| NEH | 3.09% |
| Random Search | 10.04% |

RPD is calculated as:

\[
RPD(UB) = 100 \times \frac{C_{max} - UB}{UB}
\]

Lower values are better. The GA substantially improves on Random Search and has a slightly lower overall mean RPD than NEH. **This advantage is not uniform:** NEH performs better on several larger instance groups. These results are comparisons under the documented experiment settings, not a claim that the GA is universally superior.

### Example convergence results

| Instance | GA mean best Cmax at 1,000 evaluations | GA at 50,000 | Random Search at 50,000 |
| --- | ---: | ---: | ---: |
| `tai100_10_1.fsp` | 5,958.9 | **5,464.6** | 5,980.1 |
| `tai500_20_0.fsp` | 29,057.7 | **27,534.1** | 29,161.0 |

Convergence points represent mean best-so-far makespan across 10 runs. Full tuning tables, grouped results, caveats, and analysis are in **[RESULTS.md](RESULTS.md)**.

Data files:

- [Final raw experiments](results/t6_results.csv)
- [Per-instance summary](results/instance_summary.csv)
- [Group comparison](results/group_summary.csv)
- [Convergence data](results/convergence.csv)
- [Convergence summary](results/convergence_summary.csv)

## Build

Requirements: a C++17 compiler (such as `g++`) and GNU Make.

```bash
make
```

This produces the `./pfsp` executable. To remove compiled objects and the executable:

```bash
make clean
```

## Usage

Run the GA using the tuned defaults:

```bash
./pfsp instances/tai20_5_0.fsp 42
```

Supply custom parameters (seed, population, `pc`, `pm`, tournament size):

```bash
./pfsp instances/tai20_5_0.fsp 42 50 0.8 0.4 3
```

Run the GA and both baselines on one instance (10 GA runs, 10 Random Search runs, one NEH run):

```bash
./pfsp -e instances/tai20_5_0.fsp
```

Run all ten instances in a benchmark group:

```bash
./pfsp -g 20 5
```

The `-e` and `-g` modes **append** results to `raw_results.csv`. To intentionally remove that generated file, use `./pfsp -r`. Avoid resetting the file if it contains results you want to keep.

Generate convergence observations or process previously collected results:

```bash
./pfsp -c instances/tai100_10_1.fsp
./pfsp -s results/t6_results.csv
./pfsp -cs results/convergence.csv
```

The `-c` command appends to `results/convergence.csv`; `-s` and `-cs` regenerate their respective summary CSVs. See [RESULTS.md](RESULTS.md) for the experimental methodology.

## Project Structure

```text
GenAlg/
├── README.md
├── RESULTS.md
├── Makefile
├── src/
│   ├── main.cpp
│   ├── instance.{h,cpp}
│   ├── instance_reader.{h,cpp}
│   ├── genetic_algorithm.{h,cpp}
│   ├── random_search.{h,cpp}
│   ├── neh.{h,cpp}
│   ├── metrics.{h,cpp}
│   └── experiments.{h,cpp}
├── instances/             # Taillard PFSP instances
└── results/               # Raw and aggregated experiment CSVs
```

## Scope and Limitations

- This is a **standard GA with OX** on the main branch, not a hybrid GA with local search.
- Local-search and alternative-crossover explorations live in separate branches and must be evaluated independently.
- The GA uses a fixed evaluation budget rather than a time-based stop.
- Experimental conclusions depend on the tested parameter configurations, benchmark instances, and seeds.
- The repository contains experimental data; a dedicated automated test suite is a potential next improvement.

## Author

**Pablo Jesús Moreda Vega** — Computer Engineering student at Universidad de La Laguna.