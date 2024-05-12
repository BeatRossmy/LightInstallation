struct Channel {
  int pin = 0;
  int time = 250;
  bool state = false;

  Channel(int _pin, int _time) : pin(_pin), time(_time) {} 

  void init () {
    pinMode(pin, OUTPUT);
  }
  void handle (int t) {
    if (t % time == 0) {
      state = !state;
      digitalWrite(pin, (state) ? LOW : HIGH);
    }
  }
};

const int n=16;

Channel channels [n] = {
  {26, 200},
  {27, 300},
  {28, 400},
  {29, 500},
  {30, 600},
  {31, 700},
  {32, 800},
  {33, 900},
  //
  {42, 1000},
  {43, 1100},
  {44, 1200},
  {45, 1300},
  {46, 1400},
  {47, 1500},
  {48, 1600},
  {49, 1700},
};

long t;

void setup() {
  for (int i=0; i<n; i++) channels[i].init();
}

void loop() {
  t++;
  for (int i=0; i<n; i++) channels[i].handle(t);
  delayMicroseconds(1000);
}
