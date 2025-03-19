# MAP Profiler with DDT Debugger[^1]
Most steps to use the MAP profiler are the same as the DDT debugger.

The differences are noted here.

## Compilation for profiling
- Compile programs with the `-g` flag to make source code available.
- Compile with intended optimization level, e.g., `-O2`

## Running program with MAP
The commands and steps are the same except:

- The program name to run is `map` rather than `ddt`
- Select `Profile a Program` in the _MAP_ window if the _Run_ window doesn't open

### Using reverse connect
The remote installation is located in `$TACC_MAP_DIR` once the module is loaded

[^1]: [MAP Profiler - TACC HPC Documentation](https://docs.tacc.utexas.edu/tutorials/map)
