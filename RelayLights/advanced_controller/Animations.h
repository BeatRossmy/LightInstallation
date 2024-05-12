void waveRight (Animation * a) {
  if (a->counter>=16) {
    a->reset();
    return;
  }
  a->buffer = (0x1 << (a->counter));
}

void waveLeft (Animation * a) {
  if (a->counter>=16) {
    a->reset();
    return;
  }
  a->buffer = (0x8000 >> (a->counter));
}

void random_lights (Animation * a) {
  if (a->counter>=4) {
    a->reset();
    return;
  }
  if (a->counter==0) {
    a->buffer = random(0xFFFF);
  }
}

void degrading_flash (Animation * a) {
  if (a->counter==0) {
    a->buffer = 0xFFFF;
  }
  bitWrite(a->buffer,random(16),0);

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
