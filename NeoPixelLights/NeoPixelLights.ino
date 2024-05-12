//#include <MIDI.h>

#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>
#include "util.h"
#include "RGB.h"

#define DEBUG false

#define PIXELWIDTH 85
#define PIXELHEIGHT 3
#define PIXELPIN 17

float value [8];
RGB main_color = {255,255,255};

Adafruit_NeoPixel pixels(PIXELWIDTH*PIXELHEIGHT, PIXELPIN, NEO_RBG + NEO_KHZ800);

#include "Canvas3D.h"
#include "Animations.h"

Canvas3D<PIXELWIDTH,PIXELHEIGHT> static_canvas;
Canvas3D<PIXELWIDTH,PIXELHEIGHT> fading_canvas;

elapsedMillis LEDtimer;
elapsedMillis BLINKtimer;
elapsedMillis ANIMATIONtimer;
int nextAnimation = 3000;

bool BLINKstate;

int ledTimer;

void setup() {
  Serial.begin(9600);

  usbMIDI.setHandleNoteOn(noteOn);
  usbMIDI.setHandleNoteOff(noteOff);
  usbMIDI.setHandleControlChange(controlChange);
  
  pinMode(13,OUTPUT);
  pinMode(20,OUTPUT);
  
  pixels.begin();
  pixels.clear();
  #if DEBUG
  pixels.setBrightness(10);
  #endif DEBUG
  pixels.show();
}

void loop() {
  usbMIDI.read();

  if (ledTimer>0) {
    ledTimer--;
    digitalWrite(20,HIGH);
  }
  else {
    digitalWrite(20,LOW);
  }

  if (BLINKtimer>1000) {
    BLINKtimer = 0;
    BLINKstate = !BLINKstate;
    digitalWrite(13,(BLINKstate)?HIGH:LOW);
  }
  
  
  if (LEDtimer>40) {
    LEDtimer = 0;

    Animation * animation = NULL;
    
    static_canvas.clear();
    for (int a=0; a<5; a++) {
      animation = static_animations[a];
      animation->draw(&static_canvas);
    }

    fading_canvas.mult(fmap(value[0],0,1,0.5,0.95));
    for (int a=0; a<2; a++) {
      animation = fading_animations[a];
      animation->draw(&fading_canvas);
    }

    static_canvas.add(&fading_canvas);

    pixels.clear();
    
    for (int x=0; x<PIXELWIDTH; x++) {
      for (int y=0; y<PIXELHEIGHT; y++)
        if (y%2==0) {
          pixels.setPixelColor(x+y*PIXELWIDTH, static_canvas.getColor(x,y));
        }
        else {
          pixels.setPixelColor(PIXELWIDTH-x+y*PIXELWIDTH, static_canvas.getColor(x,y));
        }
    }
    pixels.show();
  }
  
}

void noteOn (byte channel, byte note, byte velocity) {
  ledTimer = 2000;
  note = note%8;
  if (note==0)
    scanlines.trigger();
  if (note==1)
    rain.trigger();
  if (note==2)
    randomcrashes.trigger();
  if (note==3)
    noise.gate_on();
  if (note==4)
    wave.gate_on();
  if (note==5)
    flash.gate_on();
}

void noteOff (byte channel, byte note, byte velocity) {
  note = note%8;
  if (note==0) {}
  if (note==1) {}
  if (note==2) {}
  if (note==3)
    noise.gate_off();
  if (note==4)
    wave.gate_off();
  if (note==5)
    flash.gate_off();
}

void controlChange (byte channel, byte cc, byte val) {
  ledTimer = 2000;
  if (cc<8) value[cc] = float(val)/127.;

  main_color = RGB::mix({255, 48, 48},{168, 102, 22},value[3]);
  main_color = main_color.get(fmap(value[1],0,1,0.05,1));
  main_color = RGB::saturate(main_color,value[2]);
}