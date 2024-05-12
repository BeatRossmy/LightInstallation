struct Animation {
  bool active = false;
  int counter = -1;
  uint16_t buffer = 0;
  void (*func) (Animation* a) = NULL;
  
  void handle () {
    if (active) {
      counter++;
      if (func!=NULL) func(this);
    }
  }
  void reset() {
    counter = -1;
    buffer = 0;
    active = false;
  }
  void start (void * f (Animation* a)) {
    func = f; 
    active = true; 
  }
};
