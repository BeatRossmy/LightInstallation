#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();


struct Channel {
  int pin = 0;
  int time = 250;
  bool state = false;

  Channel(int _pin, int _time) : pin(_pin), time(_time) {} 

  void init () {
    pinMode(pin, OUTPUT);
  }
  void write (bool b) {
    if (b!=state) {
      digitalWrite(pin, (state) ? HIGH : LOW); 
    }
    state = b;
  }
  void handle (int t) {
    if (t % time == 0) {
      state = !state;
      digitalWrite(pin, (state) ? HIGH : LOW);
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


void handleNoteOn(byte channel, byte pitch, byte velocity) {
  if (pitch>=60 && pitch<76)
    channels[pitch-60].write(true);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  if (pitch>=60 && pitch<76)
    channels[pitch-60].write(false);
}



void setup() {
  for (int i=0; i<n; i++) channels[i].init();
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  pinMode(OUTPUT,13);
  digitalWrite(13,LOW);

  //Serial.begin(9600);
}

void loop() {
  MIDI.read();
}
