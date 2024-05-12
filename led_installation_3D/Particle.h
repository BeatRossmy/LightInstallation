struct Particle {
  float x,y;
  float dx,dy;
  int lifetime;
  RGB base_color;
  bool bounce;
  void set (float x_, float dx_, float y_, float dy_, int l, RGB rgb) {
    x = x_;
    dx = dx_;
    y = y_;
    dy = dy_;
    lifetime = l;
    base_color.set(rgb);
  }
  void move (int x_max, int y_max) {
    if (lifetime>0) lifetime--;
    x += dx;
    y += dy;
    if (x>x_max || x<0 || y>y_max || y<0) {
      lifetime = 0;
    }
  }
  void draw (Canvas3D<PIXELWIDTH,PIXELHEIGHT> * c) {
    if (lifetime<=0 || x<0 || x>=PIXELWIDTH || y<0 || y>=PIXELHEIGHT) return;
    int x_s = int(x);
    int x_e = x+1;
    float x_ratio = x-x_s;
    int y_s = int(y);
    int y_e = y+1;
    float y_ratio = y-y_s;
    RGB col = base_color.get((lifetime<0)?1:(float(lifetime)/50));
    c->add(x_s,y_s,col.get(1-x_ratio));
    c->add(x_e,y_s,col.get(x_ratio));
    // TODO: CHECK ratio???
    c->add(x_s,y_e,col.get(1-y_ratio));
    c->add(x_e,y_e,col.get(y_ratio));
  }
  void draw (Canvas3D<PIXELWIDTH,PIXELHEIGHT> * c, int min_life, int max_life) {
    if (lifetime<=0 || x<0 || x>=PIXELWIDTH || y<0 || y>=PIXELHEIGHT) return;
    int x_s = int(x);
    int x_e = x+1;
    float x_ratio = x-x_s;
    int y_s = int(y);
    int y_e = y+1;
    float y_ratio = y-y_s;
    RGB col = base_color.get((lifetime<0)?1:fmap(lifetime,min_life,max_life,0,1));
    c->add(x_s,y_s,col.get(1-x_ratio));
    c->add(x_e,y_s,col.get(x_ratio));
    // TODO: CHECK ratio???
    c->add(x_s,y_e,col.get(1-y_ratio));
    c->add(x_e,y_e,col.get(y_ratio));
  }
  void draw (Canvas3D<PIXELWIDTH,PIXELHEIGHT> * c, int y_) {
    if (lifetime<=0 || x<0 || x>=PIXELWIDTH || y<0 || y>=PIXELHEIGHT) return;
    int x_s = int(x);
    int x_e = x+1;
    float x_ratio = x-x_s;
    RGB col = base_color.get((lifetime<0)?1:(float(lifetime)/50));
    c->add(x_s,y_,col.get(1-x_ratio));
    c->add(x_e,y_,col.get(x_ratio));
  }
  bool check_collision (Particle p) {
    return (abs(x-p.x)<=0.25);
  }
};