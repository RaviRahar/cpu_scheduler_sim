///////////////////////////////////////////////
///////////////////////////////////////////////
/// All the customization can be done here only
///////////////////////////////////////////////
///////////////////////////////////////////////

#include <bits/stdc++.h>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <time.h>

#include "definations.h"
#include "Process.cpp"
#include "Process_Creator.cpp"
#include "Scheduler.cpp"
#include "Simulator.cpp"

// Redefine below if required

//#define UPPER_BOUND_ARRIVAL_TIME 10
//#define LOWER_BOUND_ARRIVAL_TIME 0
//#define UPPER_BOUND_BURST_TIME 6
//#define LOWER_BOUND_BURST_TIME 1

int main (int argc, char *argv[])
{
  std::vector<Process>  processes;

  const int no_processes = 3;
  Process_Creator Processes(no_processes);
  processes = Processes.get();

  //Process p1(3,1);
  //Process p2(6,4);
  //Process p3(1,4);
  //processes.push_back(p1);
  //processes.push_back(p2);
  //processes.push_back(p3);


  const float total_time = 1; // in secs
  const int time_quantum = 2; // in milisecs
  Simulator sim = Simulator(processes, SRTF, total_time, time_quantum);
  sim.run();
  return 0;
}
