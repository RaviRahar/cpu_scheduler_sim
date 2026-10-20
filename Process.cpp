class Process{
  static int pid;
  private:
    //const int _process_id;
    //const float _arrival_time, _burst_time;
    int _process_id;
    float _arrival_time, _burst_time;
    int _state;
    float _completion_time, _turn_around_time, _waiting_time,  _remaining_time, _response_time, _rr_priority;

  public:

    Process():
      _process_id(-1),
      _arrival_time(0),
      _burst_time(0),
      _state(EXITED),
      _completion_time(0),
      _turn_around_time(0),
      _waiting_time(0),
      _remaining_time(0),
      _response_time(0),
      _rr_priority(0)
      {}

    Process(
    const float &arrival_time, 
    const float &burst_time
    ){
      _process_id = pid++;
      _arrival_time = arrival_time;
      _burst_time = burst_time;
      _remaining_time = burst_time;
      _state = ARRIVED;

      _completion_time = _turn_around_time = _waiting_time = _response_time = _rr_priority = 0;
    }

    int set(const int &unit, const float &value){

      switch (unit) {

      case TURN_AROUND_TIME:
        _turn_around_time = value;
        return 0;
      case COMPLETION_TIME:
        _completion_time = value;
        return 0;
      case WAITING_TIME:
        _waiting_time = value;
        return 0;
      case RESPONSE_TIME:
        _response_time = value;
        return 0;
      case REMAINING_TIME:
        _remaining_time = value;
        return 0;
      case STATE:
        _state = value;
        return 0;
      case RR_PRIORITY:
        _rr_priority = value;
        return 0;

      default:
        return -1;
      }
    }

    float get(const int &unit) const {

      switch (unit) {

      case ARRIVAL_TIME:
        return _arrival_time;
      case BURST_TIME:
        return _burst_time;
      case TURN_AROUND_TIME:
        return _turn_around_time;
      case COMPLETION_TIME:
        return _completion_time;
      case WAITING_TIME:
        return _waiting_time;
      case RESPONSE_TIME:
        return _response_time;
      case REMAINING_TIME:
        return _remaining_time;
      case PROCESS_ID:
        return _process_id;
      case STATE:
        return _state;
      case RR_PRIORITY:
        return _rr_priority;

      default:
        return -1;
      }
    }

    int update(const float &completion_time){
      _completion_time = completion_time;
      _turn_around_time = _completion_time - _arrival_time;
      _waiting_time = _turn_around_time - _burst_time;
      return 0;
  }
};

int Process::pid = 0;
