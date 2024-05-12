/* MIDI RELAY LIGHT SHOW
 * 
 * notes on channel 1 trigger relay animations
 * notes on channel 2 turn on relays on noteOn controlled by params (cc70-cc77)
 * notes on other channels turn on and off relays on noteOn and noteOff messages
 */



#include <elapsedMillis.h>

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

#include "Clock.h"

#include "Relay.h"
const int n=16;
Relay channels [n] = {
  {26},{27},{28},{29},{30},{31},{32},{33},
  {42},{43},{44},{45},{46},{47},{48},{49},
};

#include "LightEvent.h"
LightEvent events [16];

int showLightEvents () {
  int buf = 0;
  unsigned long t = millis();
  for (int i=0; i<16; i++) {
    LightEvent e = events[i];
    if (e.turn_off_time>t) {
      if (e.mode==1) buf = bitWrite(buf,i,1);
      else if (e.mode==2 && (t/100)%2==0) buf = bitWrite(buf,i,1);
    }
  }
  return buf;
}

#include "Animation.h"
elapsedMillis animationTimer;
int animationPointer = 0;
Animation animationA, animationB, animationC;
Animation * animations [] = {&animationA,&animationB,&animationC};
uint16_t main_buffer;

// ANIAMTION PARAMS
int params [] = {0,0,0,0,0,0,0,0};

void update_relays (uint16_t buf) {
  for (int b=0; b<16; b++) {
    int v = bitRead(buf,b);
    if (bitRead(main_buffer,b)!=v)
      channels[b].write((v==1)?true:false);
  }
  main_buffer = buf;
}

#include "Animations.h"

void handleControlChange(byte channel, byte number, byte value) {
  int p = number-70;
  if (p>=0 && p<8) {
    params[p] = value;
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel==1) {
    int a = pitch%FUNCTIONS;
    animations[animationPointer]->start(animation_functions[a]);
    animationPointer = (animationPointer+1)%3;
  }
  else if (channel==2) {
    byte rel = pitch%16;
    byte mode = (params[1]>64)?2:1;
    unsigned long t = millis() + params[0]*10;
    events[rel] = {rel,mode,t};
  }
  else {
    int rel = pitch%16;
    channels[rel].write(true);
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  if (channel>2) {  
    int rel = pitch%16;
    channels[rel].write(false);
  }
}

void setup() {
  for (int i=0; i<n; i++) channels[i].init();

  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleStart(onStart);
  MIDI.setHandleClock(onClock);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  MIDI.read();

  long step = clock.changed();
  if (step>-1) {
    uint16_t buf = 0;
    for (int i=0; i<3; i++) {
      animations[i]->handle();
      buf = buf | animations[i]->buffer;
    }

    buf = buf | showLightEvents();
    
    update_relays(buf);
  }

  /*if (animationTimer>12) {
    animationTimer = 0;

    uint16_t buf = 0;
    for (int i=0; i<3; i++) {
      animations[i]->handle();
      buf = buf | animations[i]->buffer;
    }

    buf = buf | showLightEvents();
    
    update_relays(buf);
  }*/
  
}
