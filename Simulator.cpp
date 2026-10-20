class Simulator{
  private:
    const std::vector<Process> _processes;
    const int _scheduler;
    const int _time_total;
    const int _time_quantum;

    std::vector<Process> _final_processes_status;


    std::ofstream _processes_status;
    std::ofstream _scheduling_status;

  public:

    Simulator(
      const std::vector<Process> &processes, 
      const int &scheduler, 
      const float &time_total,
      const int &time_quantum
      ):
      _processes(processes), 
      _scheduler(scheduler), 
      _time_total(static_cast<int>(std::lround(time_total*1000))),
      _time_quantum(time_quantum)
      {}


    void run(){
      open_files(",");

      Scheduler sched = Scheduler(_scheduler, _time_quantum);
      std::vector<bool> is_admitted(_processes.size(), false);
      for(int time_unit = 0; time_unit < _time_total; time_unit++){
        for(std::size_t ind = 0; ind < _processes.size(); ind++){
          Process proc = _processes[ind];

          if(!is_admitted[ind] && proc.get(ARRIVAL_TIME) <= sched.get(TIME_SPENT)){

            sched.add_task(proc);
            is_admitted[ind] = true;
            save_processes_status(proc);
            save_status_txt(sched, proc, ",");
          }

        }

        save_status_txt(
            sched,
            save_processes_status(sched.run_next()),
            ","
        );

      }

      save_processes_txt(",");

      close_files();
    }


    Process save_processes_status(const Process &process){
      if (process.get(PROCESS_ID) >= 0){
        int is_new_proc = 1;
        for(std::size_t ind=0; ind < _final_processes_status.size(); ind++){
          if(_final_processes_status[ind].get(PROCESS_ID) == process.get(PROCESS_ID)){
            _final_processes_status[ind] = process;
            is_new_proc = 0;
          }
        }
        if (is_new_proc == 1){_final_processes_status.push_back(process);}
      }
      return process;
    }

    void save_status_txt(const Scheduler &sched, const Process &process, const std::string &delimiter){
      if (process.get(PROCESS_ID) >= 0){

        _scheduling_status << sched.get(TIME_SPENT) << delimiter;
        _scheduling_status << process.get(PROCESS_ID) << delimiter;
        _scheduling_status << decode_state(process.get(STATE)) << "\n";
      }
    }

    void save_processes_txt(const std::string &delimiter){
      for(auto process: _final_processes_status){
        _processes_status << process.get(PROCESS_ID) << delimiter;
        _processes_status << process.get(ARRIVAL_TIME) << delimiter;
        _processes_status << process.get(BURST_TIME) << delimiter;
        _processes_status << process.get(COMPLETION_TIME) << delimiter;
        _processes_status << process.get(TURN_AROUND_TIME) << delimiter;
        _processes_status << process.get(WAITING_TIME) << delimiter;
        _processes_status << process.get(RESPONSE_TIME) << "\n";
      }
    }

    std::string decode_state(const int &state){
      switch (state) {
        case ARRIVED:
          return "ARRIVED";
        case RUNNING:
          return "RUNNING";
        case EXITED:
          return "EXITED";
        default:
          return "ERROR";
      }
    }

    void open_files(const std::string &delimiter){

      _scheduling_status.open("status.txt");
      _scheduling_status << "MILLISECOND_NUMBER" << delimiter;
      _scheduling_status << "PROCESS_ID" << delimiter;
      _scheduling_status << "STATUS" << "\n";


      _processes_status.open("processes.txt");
      _processes_status << "PROCESS_ID" << delimiter;
      _processes_status << "ARRIVAL_TIME" << delimiter;
      _processes_status << "BURST_TIME" << delimiter;
      _processes_status << "COMPLETION_TIME" << delimiter;
      _processes_status << "TURN_AROUND_TIME" << delimiter;
      _processes_status << "WAITING_TIME" << delimiter;
      _processes_status << "RESPONSE_TIME" << "\n";
    }

    void close_files(){
      _processes_status.close();
      _scheduling_status.close();
    }

};
