template<int X_SIZE, int Y_SIZE>
struct Canvas3D {
  RGB pixels [X_SIZE][Y_SIZE];

  void clear () {
    for (int x=0; x<X_SIZE; x++) {
      for (int y=0; y<Y_SIZE; y++) pixels[x][y] = {0,0,0};
    }
  }

  void set (int x, int y, RGB rgb) {
    pixels[x][y].set(rgb);  
  }

  void add (int x, int y, RGB rgb) {
    set(x,y,RGB::add(get(x,y),rgb));
  }

  void add (Canvas3D * c) {
    for (int x=0; x<X_SIZE; x++) {
      for (int y=0; y<Y_SIZE; y++) add(x,y,c->get(x,y));
    }
  }

  RGB get (int x, int y) {
    return pixels[x][y];  
  }

  uint32_t getColor (int x, int y) {
    return pixels[x][y].get();  
  }

  void add (RGB rgb) {
    for (int x=0; x<X_SIZE; x++) {
      for (int y=0; y<Y_SIZE; y++) set(x,y,RGB::add(get(x,y),rgb));
    }
  }

  void mix (RGB rgb, float m) {
    for (int x=0; x<X_SIZE; x++) {
      for (int y=0; y<Y_SIZE; y++) set(x,y,RGB::mix(get(x,y),rgb,m));
    }
  }

  void mult (float v) {
    for (int x=0; x<X_SIZE; x++) {
      for (int y=0; y<Y_SIZE; y++) set(x,y,get(x,y).get(v));
    }
  }
};
