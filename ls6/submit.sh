#!/bin/bash
#SBATCH -J myjob           # Job name
#SBATCH -o myjob.o%j       # Name of stdout output file
#SBATCH -e myjob.e%j       # Name of stderr error file
#SBATCH -p development     # Queue (partition) name
#SBATCH -N 1               # Total # of nodes (must be 1 for serial)
#SBATCH -n 4               # Total # of mpi tasks (should be 1 for serial)
#SBATCH -t 00:10:00        # Run time (hh:mm:ss)
#SBATCH -A ASC23014        # Project/Allocation name (req'd if you have more than 1)

date

source env.sh

ddt --connect -n $SLURM_NPROCS ../mpi/deadlock

date
