> **Note:** This is an old class project made for an OS + OOP lecture.

# CPU Scheduler Simulator

A small C++ simulator for these CPU scheduling algorithms:

- First Come First Serve (FCFS)
- Shortest Remaining Time First (SRTF)
- Round Robin (RR)

## Build and run

GNU Make and a C++17 compiler such as `g++` are required.

```sh
make
make run
```

The build creates `cpu_scheduler_sim`. Running it creates:

- `status.txt` : the process selected and its state at each relevant tick
- `processes.txt` : final timing metrics for each admitted process

Use `make clean` to remove the executable and generated output files.

## Configuration

Edit `main.cpp` to select `FCFS`, `SRTF`, or `RR`, and to set the process count, simulation duration, and Round Robin quantum. Random arrival and burst-time bounds are defined in `definations.h`.
