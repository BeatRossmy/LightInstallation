uint16_t shift (uint16_t bits, int d) {
  if (d==0) return bits;
  uint16_t l_bits = 0;
  uint16_t r_bits = 0;
  if (d>0) {
    d = d%32;
    l_bits = (bits>>d) & (0x7FFFFFFF>>(d-1));
    r_bits = bits<<(RELAYS-d);
  }
  else if (d<0) {
    d = -d;
    l_bits = bits<<d;
    r_bits = (bits>>(RELAYS-d)) & (0x7FFFFFFF>>(RELAYS-1-d));
  }
  return (l_bits | r_bits);
}
