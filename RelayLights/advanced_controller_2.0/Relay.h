struct Relay {
  int pin = 0;
  bool state = false;
  Relay(int _pin) : pin(_pin) {} 
  void init () {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); 
  }
  void write (bool b) {
    if (b!=state) {
      digitalWrite(pin, (state) ? HIGH : LOW); 
    }
    state = b;
  }
};
