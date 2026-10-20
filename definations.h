// Process.cpp

#define ARRIVAL_TIME 0
#define BURST_TIME 1
#define COMPLETION_TIME 2
#define TURN_AROUND_TIME 3
#define WAITING_TIME 4
#define RESPONSE_TIME 5
#define REMAINING_TIME 6
#define PROCESS_ID 7
#define STATE 8
#define RR_PRIORITY 9

#define ARRIVED 0
#define RUNNING 1
#define EXITED 2

// Process_Creator.cpp
#define _for_(i, n) for(int i=0; i<n; i++)

///////////////////////////////////
///////////CUSTOMISABLE////////////
///////////////////////////////////
#define UPPER_BOUND_ARRIVAL_TIME 10
#define LOWER_BOUND_ARRIVAL_TIME 0
#define UPPER_BOUND_BURST_TIME 6
#define LOWER_BOUND_BURST_TIME 1
///////////////////////////////////

// Scheduler.cpp
  // First Come First Serve
#define FCFS 0
  // Shortest Remaining Time First
#define SRTF 1
  // Round Robin
#define RR 2


#define TIME_SPENT 0
#define SCHEDULER 1
