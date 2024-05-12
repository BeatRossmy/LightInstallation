template<int SIZE>
struct Canvas {
  RGB pixels [SIZE];

  void clear () {
    for (int i=0; i<SIZE; i++) pixels[i] = {0,0,0};
  }

  void set (int index, RGB rgb) {
    pixels[index].set(rgb);  
  }

  void add (int index, RGB rgb) {
    set(index,RGB::add(get(index),rgb));
  }

  void add (Canvas * c) {
    for (int i=0; i<SIZE; i++)
      add(i,c->get(i));
  }

  RGB get (int index) {
    return pixels[index];  
  }

  uint32_t getColor (int index) {
    return pixels[index].get();  
  }

  void add (RGB rgb) {
    for (int i=0; i<SIZE; i++) set(i,RGB::add(get(i),rgb));
  }

  void mix (RGB rgb, float m) {
    for (int i=0; i<SIZE; i++) set(i,RGB::mix(get(i),rgb,m));
  }

  void mult (float v) {
    for (int i=0; i<SIZE; i++) set(i,get(i).get(v));
  }
};
