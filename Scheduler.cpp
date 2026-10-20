struct STRUCT_FCFS{
    bool operator()(const Process &p1, const Process &p2)
    {
        if (p1.get(ARRIVAL_TIME) > p2.get(ARRIVAL_TIME)){return 1;}
        else if ((p1.get(ARRIVAL_TIME) == p2.get(ARRIVAL_TIME))){
          return p1.get(PROCESS_ID) > p2.get(PROCESS_ID);
        }
        else{return 0;}
    } 
};


struct STRUCT_SRTF{
    bool operator()(const Process &p1, const Process &p2)
    {
        if (p1.get(REMAINING_TIME) != p2.get(REMAINING_TIME)){
          return p1.get(REMAINING_TIME) > p2.get(REMAINING_TIME);
        }
        if (p1.get(ARRIVAL_TIME) != p2.get(ARRIVAL_TIME)){
          return p1.get(ARRIVAL_TIME) > p2.get(ARRIVAL_TIME);
        }
        return p1.get(PROCESS_ID) > p2.get(PROCESS_ID);
    }
};

struct STRUCT_RR{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.get(RR_PRIORITY) > p2.get(RR_PRIORITY);
    }
};


class Scheduler{
  private:

    // Required for all algos
    const int _scheduler;
    int _time_spent;

    // Required for RR only
    const int _time_quantum;
    int _time_spent_ind; //time spent by individual processes
    int _rr_priority_tracker; // tracks maximum value or minimum priority for RR

    std::priority_queue<Process, std::vector<Process>, STRUCT_FCFS> _ready_queue_fcfs;
    std::priority_queue<Process, std::vector<Process>, STRUCT_SRTF> _ready_queue_srtf;
    std::priority_queue<Process, std::vector<Process>, STRUCT_RR> _ready_queue_rr;

  public:

    Scheduler(
    const int &scheduler, 
    const int &time_quantum
    ): 
    _scheduler(scheduler), 
    _time_quantum(time_quantum)
    {
    _time_spent = _time_spent_ind = _rr_priority_tracker = 0;
    }

    Process add_task(const Process &process){
      switch (_scheduler) {
        case FCFS: {_ready_queue_fcfs.push(process); return process;}
        case SRTF: {_ready_queue_srtf.push(process); return process;}
        case RR: {Process p = process; p.set(RR_PRIORITY, _rr_priority_tracker++); _ready_queue_rr.push(p); return process;}
        default: {std::cout<< "\nError in Scheduler::add_task()\n"; return Process();}
      }
    }

    Process run_next(){
      switch (_scheduler) {
        case FCFS:{

          if (!_ready_queue_fcfs.empty()){

            Process proc = _ready_queue_fcfs.top(); 
            _ready_queue_fcfs.pop();

            if(proc.get(REMAINING_TIME) == proc.get(BURST_TIME)){
              proc.set(RESPONSE_TIME, _time_spent-proc.get(ARRIVAL_TIME));
            }

            _time_spent++;


            proc.set(REMAINING_TIME, proc.get(REMAINING_TIME)-1); 

            if(proc.get(REMAINING_TIME) == 0){
              proc.update(_time_spent);
              proc.set(STATE, EXITED);
            }
            else{
              proc.set(STATE, RUNNING);
              _ready_queue_fcfs.push(proc);
            }

            return proc;
          }

          else{_time_spent++; return Process();}
        }

        case SRTF:{

          if (!_ready_queue_srtf.empty()){

            Process proc = _ready_queue_srtf.top(); 
            _ready_queue_srtf.pop();

            if(proc.get(REMAINING_TIME) == proc.get(BURST_TIME)){
              proc.set(RESPONSE_TIME, _time_spent-proc.get(ARRIVAL_TIME));
            }

            _time_spent++;


            proc.set(REMAINING_TIME, proc.get(REMAINING_TIME)-1); 

            if(proc.get(REMAINING_TIME) == 0){
              proc.update(_time_spent);
              proc.set(STATE, EXITED);
            }
            else{
              proc.set(STATE, RUNNING);
              _ready_queue_srtf.push(proc);
            }

            return proc;
          }

          else{_time_spent++; return Process();}
        }

        case RR:{

          if (!_ready_queue_rr.empty()){

            Process proc = _ready_queue_rr.top(); 
            // pop the process based on our priority criteria
            // will push_back later if required
            _ready_queue_rr.pop();

            // just to set response time, checks if this is first time execution of process
            if(proc.get(REMAINING_TIME) == proc.get(BURST_TIME)){
              proc.set(RESPONSE_TIME, _time_spent-proc.get(ARRIVAL_TIME));
            }

            // substracts 1 from remaining time, simulation work done
            proc.set(REMAINING_TIME, proc.get(REMAINING_TIME)-1); 

            // time spent by scheduler overall is increased by 1
            _time_spent++;
            // time spent by scheduler on this process is increased by 1
            _time_spent_ind++;

            // if no more work to do, exit
            if(proc.get(REMAINING_TIME) == 0){
              proc.update(_time_spent);
              proc.set(STATE, EXITED);
              _time_spent_ind = 0;
            }
            // if still work to do but time spent on process reached time quantum, move it to the back
            // also set _time_spent_ind to 0 for new process
            else if(_time_spent_ind >= _time_quantum){
              proc.set(STATE, RUNNING);
              proc.set(RR_PRIORITY, _rr_priority_tracker++);
              _ready_queue_rr.push(proc);
              _time_spent_ind = 0;
            }
            // else just do work and push, keeping its current position at the front
            else{
              proc.set(STATE, RUNNING);
              _ready_queue_rr.push(proc);
            }

            return proc;
          }

          else{_time_spent++; return Process();}
        }
        default:{std::cout<< "\nError in Scheduler::run_next()\n"; return Process();}
      }
    }


    int get(const int &unit) const {

      switch (unit) {

      case TIME_SPENT:
        return _time_spent;
      case SCHEDULER:
        return _scheduler;

      default:
        return -1;
      }
    }
};
