#include "Animation.h"

class RandomCrashes : public Animation {
public:
  Particle sparks[30];

  RandomCrashes(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    for (int i = 0; i < 30; i++) sparks[i].move(PIXELWIDTH,PIXELHEIGHT);
    for (int i = 0; i < 30; i++) sparks[i].draw(c, min_life, max_life);
  }

  void trigger() {
    float x = random(PIXELWIDTH);
    float y = random(PIXELHEIGHT);
    int n = 0;
    int count = (int)fmap(value[0],0,1,1,10);
    for (int i = 0; i < 30; i++) {
      if (sparks[i].lifetime==0) {
        int l = random(min_life, max_life);
        float dx = random_speed(BIDIRECTIONAL, min_speed, max_speed);
        float dy = random_speed(BIDIRECTIONAL, min_speed, max_speed);
        sparks[i].set(x, dx, y, dy, l, main_color);
        n++;
      }
      if (n==count) return;
    }
  }
};
RandomCrashes randomcrashes(0,12,1,30);

class ScanLines : public Animation {
public:
  Particle particles[30];

  ScanLines(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  virtual void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    for (int i = 0; i < 30; i++) particles[i].move(PIXELWIDTH,PIXELHEIGHT);
    for (int i = 0; i < 30; i++) {
      particles[i].draw(c);
    }
  }

  void trigger() {
    int n=0;
    int count = (int)fmap(value[0],0,1,1,10);
    for (int i = 0; i < 30; i++) {
      if (particles[i].lifetime == 0) {
        int l = 10000;
        float x = 0+(n++);
        float dx = 5.25;
        particles[i].set(x, dx, 0, 0, l, main_color);
        if (n==count) return;
      }
    }
  }
};
ScanLines scanlines(0,0,10,50);

class Wave : public Animation {
public:
  Wave(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    if (gate) {
      float min = fmap(value[0],0,1,-2,0);
      int l = PIXELWIDTH/3;
      float t = millis();
      for (int i = 0; i < l; i++) {
        float phase = float(i) / float(l) * PI * 2.0;
        float vA = (sin(t / fmap(value[0],0,1,500,100) + phase) + 1) / 2.0;
        RGB a = main_color.get(fmap(vA,0,1,min,1));
        for (int n=0; n<3; n++) {
          for (int y=0; y<PIXELHEIGHT; y++) {
            c->add(i+n*l,y, a);
          }
        }
      }
    }
  }
};
Wave wave(0,0,0,0);

class Noise : public Animation {
public:
  Noise(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    if (gate) {
      long thr = (long)map(value[0], 0, 1, 98, 50);
      for (int x = 0; x < PIXELWIDTH; x++) {
        for (int y = 0; y < PIXELHEIGHT; y++) {
          if ((long)random(100) > thr) {
            c->add(x,y, main_color);
          }
        }
      }
    }
  }
};
Noise noise(0,0,0,0);

class Flash : public Animation {
public:
  Flash(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    if (gate) {
      RGB col = main_color.get(fmap(value[0], 0, 1, 0.1, 0.5));
      for (int x = 0; x < PIXELWIDTH; x++) {
        for (int y = 0; y < PIXELHEIGHT; y++) {
          c->add(x,y, col);
        }
      }
    }
  }
};
Flash flash(0,0,0,0);

class SeaLine : public Animation {
public:
  Particle particles[10];

  SeaLine(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void activateParticle() {
    for (int i = 0; i < 10; i++) {
      if (particles[i].lifetime == 0) {
        int l = random(min_life, max_life);
        float x = 0;
        float dx = random_speed(RIGHT, min_speed, max_speed);
        float y = (int)random(PIXELHEIGHT);
        float dy = 0;
        
        particles[i].set(x, dx, y, dy, l, main_color);
        return;
      }
    }
  }
  virtual void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    for (int i = 0; i < 10; i++) particles[i].move(PIXELWIDTH,PIXELHEIGHT);
    for (int i = 0; i < 10; i++) particles[i].draw(c);
  }
  void trigger() {
    activateParticle();
  }
};
SeaLine sealine(50,500,13,20);

class Rain : public Animation {
public:

  Rain(int min_l, int max_l, int min_s, int max_s)
    : Animation(min_l,max_l,min_s,max_s) {}

  void draw(Canvas3D<PIXELWIDTH,PIXELHEIGHT>* c) {
    if (triggered) {
      int x = random(PIXELWIDTH);
      int y = random(PIXELHEIGHT);
      c->set(x,y, main_color);
      triggered = false;
    }
  }
  void trigger() {
    triggered = true;
  }
};
Rain rain(0,0,0,0);

Animation* static_animations[] = {
  &wave,
  &scanlines,
  &randomcrashes,
  &noise,
  &flash
};

Animation* fading_animations[] = {
  &sealine,
  &rain
};