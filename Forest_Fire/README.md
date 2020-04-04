# Forest Fire

Forest Fire is a program that simulates a forest fire.  Fires can only spread between adjacent trees in the four cardinal directions.  The amount of trees in the simulation as well as the spread rate can be manipulated in the program.  This program can be run in parallel using mpi.

There are two versions of this program:  

forestFire.c is the standard forestfire simulation
forestFirePlot.c was the file used to generate a plot of the burn rate of a forest when the p value was manipulated
forestFireMPI.c runs the simulation in parallel across several computers

Please note that these simulations were run on TJ's computer network, and may not work as expected on home computers.  

## forestFire

This program simulates a forest fire.  Fires can only spread between adjacent trees in the four cardinal directions.  The amount of trees in the simulation as well as the spread rate can be manipulated in the program.

  To run this program use the following commands:

    gcc forestFire.c
    ./a.out

This should generate a simulation of a textbased forest fire.
  
This should produce a series of an output similiar to the one below.

![Forest Fire](https://raw.githubusercontent.com/zac-ng/Parallel_Computing/main/Forest_Fire/forestFire.gif)

## forestFirePlot

This program was used to determine to compare the burn rate of the forest when the p value was varied.  Fires can only spread between adjacent trees in the four cardinal directions.  The amount of trees in the simulation as well as the spread rate can be manipulated in the program.

  To run this program use the following commands:

    gcc forestFirePlot.c
    ./a.out

This should display the burn rate of the forest.

## forestFireMPI

This program simulates a forest fire running in parallel using mpi.  The workload is distributed across several machines.  The work time can decrease by adding more workers to the hostfile.  Fires can only spread between adjacent trees in the four cardinal directions.  The amount of trees in the simulation as well as the spread rate can be manipulated in the program.

  To run this program use the following commands:

    mpicc forestFireMPI.c
    time mpirun -machinefile hostlist.txt a.out

This should generate a simulation of a textbased forest fire.  Please note that this may not work as expected if you run on a home computer, as it was designed to be run on TJ's computer network.


