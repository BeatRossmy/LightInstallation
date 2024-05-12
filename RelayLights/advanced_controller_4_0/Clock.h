bool ext_clock = false;
unsigned long clock_time;

struct Clock {
  long step = -1;
  int time = 21; // => 1/4 at 120 bpm = 500ms => 24ppq = 20.83ms
  unsigned long last_pulse = 0;
  bool ext_clock = false;
  bool new_pulse = false;
  long changed () {
    if (new_pulse) {
      new_pulse = false;
      return step;
    }
    else return -1;
  }
};

Clock clock = {};

void onStart () {
  clock.step = -1;  
}

void onClock () {
  clock.step++;
  clock.last_pulse = millis();
  clock.new_pulse = true;
  // do stuff
}

void onStop () {}

void onContinue () {}
