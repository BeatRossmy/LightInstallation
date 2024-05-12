float fmap (float value, float in_low, float in_high, float out_low, float out_high) {
  return ((value-in_low)/(in_high-in_low)*(out_high-out_low)+out_low);
}

bool coin () {
  return (random(100)>50);
}