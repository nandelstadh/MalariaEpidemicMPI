# Malaria Epidemic Simulation Using the SSA Algorithm with MPI

### Overview

We have implemented a parallel version of the SSA algorithm in order to simulate a malaria epidemic. The program is designed for distributed-memory architectures and uses MPI. 

### Dependencies

Everything has been tested and should run without problems on new versions MacOS and Linux. If you are using Windows, consider not using Windows. The performance tests were done on the Uppsala University cluster Pelle.
Dependencies are

```
OpenMPI
Python
Matplotlib
```

If running the slurm script on Pelle, it will make sure that these modules are loaded.

### Build
To download and make the executable, simply run

```
$ git clone https://github.com/nandelstadh/MalariaEpidemicMPI/
$ cd MalariaEpidemicMPI
$ make
```

### Run

Run the executable using 

```
$ mpirun -np p ./main N
```

where p is the number of processes and N is the number of times the simulation is run. Note that we require that p divides N. A histogram of the number of susceptible humans at the end of the simulations is then saved in ./data.
Other information is printed to the terminal as

```
$ min max t25 t50 t75 t100 tmax N P
```

where

1. min: left end of histogram
2. max: right end of historgram
3. t25: average time taken to simulate the times 0 to 25
4. t50: average time taken to simulate the times 25 to 50
5. t75: average time taken to simulate the times 50 to 75
6. t100: average time taken to simulate the times 75 to 100
7. N: number of simulations
8. p: number of processors

To run a small battery of simulations (this requries 32 available cores, and the ability for MPI to bind cores), run

```
$ cd scripts
$ ./demonstrations.sh
```

This will run the program three different times with N=10^7, N=20^7 and N=40^7 simulations respectively. The histograms are then found in the folder data, and the output in the folder results.


