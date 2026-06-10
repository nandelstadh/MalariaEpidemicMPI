# Malaria Epidemic Simulation Using the SSA Algorithm with MPI

### Overview

We have implemented a parallel version of the SSA algorithm in order to simulate a malaria epidemic. The program is designed for distributed-memory architectures and uses MPI. 

### Dependencies

Everything has been tested and should run without problems on new versions MacOS and Linux. If you are using Windows, consider not using Windows. The performance tests were done on the Uppsala University cluster Pelle.
Dependencies are

```
GCC
OpenMPI
Python
Matplotlib
```
Make sure that these modules are loaded before running the program or any script which calls the program.

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
$ mpirun -np p ./main N a
```

where p is the number of processes and N is the number of times the simulation is run, and a is a boolean representing if the average times per processor and interval should be printed. Note that we require that p divides N. A histogram of the number of susceptible humans at the end of the simulations is then saved in ./data.
Other information is printed to the terminal as

```
$ min max t25 t50 t75 t100 tmax N P
```

where

1. min: left end of histogram
2. max: right end of historgram
3. N: number of simulations
4. p: number of processors
5. tmax: total time taken

If main is called with a=1, a table with columns representing average time per quartile, and row representing processor, is also printed. 

To run a small battery of simulations (this requries 32 available cores, and the ability for MPI to bind cores), run

```
$ cd scripts
$ chmod u+x demonstration.sh
$ ./demonstration.sh
```

This will run the program three different times with N=1*10^6, N=2*10^6 and N=4*10^6 simulations respectively. The histograms are then found in the folder data, and the output in the folder results.

Note that on Pelle, you might get an error like

```
$ osc_ucx_component.c:369  Error: OSC UCX component priority set inside component query failed
```

But this just means that OpenMPI uses a different backend, and should not affect the accuracy of results. To get rid of this error, one may also run OpenMPI with the extra flag --mca osc ^ucx.

