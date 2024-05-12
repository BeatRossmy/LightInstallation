#define BIDIRECTIONAL 0
#define LEFT -1
#define RIGHT 1

class Animation {
public:
  bool triggered;
  bool gate = false;
  int min_life = 0;
  int max_life = 12;
  int min_speed = 15;
  int max_speed = 30;

  Animation(int min_l, int max_l, int min_s, int max_s) {
    min_life = min_l;
    max_life = max_l;
    min_speed = min_s;
    max_speed = max_s;
  }

  void handle (Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    if (triggered || gate) {
      trigger();
      triggered = false;
    }
    draw(c);
  }

  virtual void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {}

  virtual void init() {}

  virtual void trigger() {}

  void set_trigger (bool b) {
    triggered = b;
  }

  void gate_on() {
    gate = true;
  }

  void gate_off() {
    gate = false;
  }

  float random_speed(int dir, float min, float max) {
    float speed = float(random(min * 100, max * 100)) / (40. * 100);
    if (dir == 0)
      return speed * ((coin()) ? -1 : 1);
    else
      return speed * ((dir > 0) ? 1 : -1);
  }
};

#include "Particle.h"