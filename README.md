# DDT Debugger on TACC[^1]

## Compilation for debugging
Compile programs with flags `-g -O0`
```bash
$ mpiCC -g -O0 prog.c
```

## Running program with DDT
There are 2 methods to run your program with DDT.
Using X11 forwarding doesn't require additional software, only X11 forwarding.
Due to the GUI being forwarded from the server to your computer, it is slower (lag).
Using reverse connect requires installation of DDT's remote client.

### Using X11 forwarding
1) The ssh connection to TACC must enable X11 forwarding by either:
- `ssh -X lonestar` the `-X` flag enables X forwarding, and _should_ work
- `ssh -Y lonestar` the `-Y` flag enables trusted X forwarding, and will work
2) Setup/activate environment
3) Start the debugger: `ddt ./a.out`
- The error message `ddt: cannot connect to X server` indicates a problem with X forwarding
4) Select `Run and Debug a Program` in the _DDT_ window
5) Verify application, set arguments and job specifications in the _Run_ window
- Ensure the _MPI Implementation_ that is set matches the MPI used in compilation

Select `Submit` and a job submission status window will appear.
The DDT GUI will appear when the job is launched.

### Using reverse connect
The remote installation is located in `$TACC_DDT_DIR` once the module is loaded
1) Install [Linaro Forge remote client](https://www.linaroforge.com/download-documentation)
- Use of the remote client doesn't require a license (the license is required on the remote system)
2) Create a configuration in `Remote Launch` for login name and cluster
3) Connect to the configuration and login to the cluster as when using ssh
4) From a separate terminal window (connected via ssh) submit the job with sbatch
- Replace `ibrun` with `ddt --connect -n $SLURM_NPROCS ./a.out`

When the job is launched the remote client will prompt to accept the connection.

[^1]: [DDT Debugger - TACC HPC Documentation](https://docs.tacc.utexas.edu/tutorials/ddt)
