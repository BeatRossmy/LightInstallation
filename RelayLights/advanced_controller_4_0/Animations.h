void waveRight (Animation * a) {
  if (a->counter>=RELAYS) {
    a->reset();
    return;
  }
  a->buffer = (0x1 << (a->counter));
}

void waveLeft (Animation * a) {
  if (a->counter>=RELAYS) {
    a->reset();
    return;
  }
  //a->buffer = (0x8000 >> (a->counter));
  uint16_t mask = 0x1<<(RELAYS-1);
  a->buffer = (mask >> (a->counter));
}
void waveDouble (Animation * a) {
  if (a->counter>=RELAYS) {
    a->reset();
    return;
  }
  a->buffer = shift(1,a->counter) | shift(1,-a->counter);
}

void random_lights (Animation * a) {
  if (a->counter>0) {
    a->reset();
    return;
  }
  if (a->counter==0) {
    uint16_t mask = 0xFFFF>>(16-RELAYS);
    a->buffer = random(mask);
  }
}

void degrading_flash (Animation * a) {
  if (a->counter==0) {
    uint16_t mask = 0xFFFF>>(16-RELAYS);
    a->buffer = mask;
  }
  for (int n=0; n<4; n++)
    bitWrite(a->buffer,random(RELAYS),0);

  if (a->buffer==0) {
    a->reset();
    return;
  }
}

const int FUNCTIONS = 4;
void (* animation_functions []) (Animation* a) = {
  &waveRight,
  &waveLeft,
  &random_lights,
  &degrading_flash
};
