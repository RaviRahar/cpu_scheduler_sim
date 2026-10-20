class Process_Creator{

  private:
    std::vector<Process> processes;

  public:

    Process_Creator(const int &no_processes){
      std::srand(time(0));
      float arrival_time, burst_time;

      _for_(i, no_processes){
        arrival_time = std::rand() % (UPPER_BOUND_ARRIVAL_TIME - LOWER_BOUND_ARRIVAL_TIME) + LOWER_BOUND_ARRIVAL_TIME;
        burst_time = std::rand() % (UPPER_BOUND_BURST_TIME - LOWER_BOUND_BURST_TIME) + LOWER_BOUND_BURST_TIME;
        //arrival_time = 4*std::round(1000*(float)(std::rand()/RAND_MAX))/1000;
        //burst_time = 4*std::round(1000*(float)(std::rand()/RAND_MAX))/1000;
        processes.push_back(Process(arrival_time, burst_time));
    }

  }
    std::vector<Process> get(){return processes;}
};
