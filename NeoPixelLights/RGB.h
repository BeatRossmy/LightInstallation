struct RGB {
  uint8_t r,g,b;
  
  void set (uint8_t _r, uint8_t _g, uint8_t _b) {
    r = _r;
    g = _g;
    b = _b;
  }

  void set (RGB rgb) {
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
  }

  uint32_t get () {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }

  RGB get (float v) {
    if (v<0) v = 0;
    if (v>1) v = 1;
    return {uint8_t(float(r)*v), uint8_t(float(g)*v), uint8_t(float(b)*v)};
  }

  static RGB mix (RGB c1, RGB c2) {
    return mix(c1,c2,0.5);
  }

  static RGB mix (RGB c1, RGB c2, float m) {
    float r = float(c1.r)*(1.-m)+float(c2.r)*(m);
    if (r>255) r = 255;
    float g = float(c1.g)*(1.-m)+float(c2.g)*(m);
    if (g>255) g = 255;
    float b = float(c1.b)*(1.-m)+float(c2.b)*(m);
    if (b>255) b = 255;
    return {uint8_t(r),uint8_t(g),uint8_t(b)};
  }
  static RGB mix (RGB c1, RGB c2, RGB c3, float m) {
    //Serial.println(m);
    if (m<=0.5) return mix(c1,c2,m*2);
    return mix(c2,c3,(m*2.)-1.);
  }

  static RGB add (RGB c1, RGB c2) {
    uint8_t r = constrain(c1.r+c2.r,0,255);
    uint8_t g = constrain(c1.g+c2.g,0,255);
    uint8_t b = constrain(c1.b+c2.b,0,255);
    return {r,g,b};
  }
  
  static RGB sub (RGB c1, RGB c2) {
    uint8_t r = constrain(c1.r-c2.r,0,255);
    uint8_t g = constrain(c1.g-c2.g,0,255);
    uint8_t b = constrain(c1.b-c2.b,0,255);
    return {r,g,b};
  }

  static RGB saturate (RGB c, float s) {
    int average = (c.r+c.g+c.b)/3;
    uint8_t r = (uint8_t)fmap(s,0,1,average,c.r);
    uint8_t g = (uint8_t)fmap(s,0,1,average,c.g);
    uint8_t b = (uint8_t)fmap(s,0,1,average,c.b);
    return {r,g,b};
  }
};

//https://coolors.co/2b3a67-496a81-66999b-b3af8f-ffc482
//https://www.rapidtables.com/convert/color/hex-to-rgb.html

RGB scheme_0 [] = {
  {184, 51, 106},
  {196, 144, 209},
  {172, 172, 222},
  {171, 218, 252},
  {229, 252, 255}
};

RGB scheme_1 [] = {
  {235, 233, 233},
  {243, 248, 242},
  {53, 129, 184},
  {252, 176, 126},
  {222, 226, 214}
};

RGB scheme_2 [] = {
  {144, 252, 249},
  {99, 180, 209},
  {118, 153, 212},
  {148, 72, 188},
  {72, 3, 85}
};

RGB scheme_3 [] = {
  {43, 58, 103},
  {73, 106, 129},
  {102, 153, 155},
  {179, 175, 143},
  {255, 196, 130}
};

RGB * schemes [] = {
  scheme_0,
  scheme_1,
  scheme_2,
  scheme_3
};

int scheme = 0;
float dim = 0.7;

RGB frst_color = schemes[scheme][0].get(dim);
RGB scnd_color = schemes[scheme][2].get(dim);
RGB thrd_color = schemes[scheme][4].get(dim);

void randomize_scheme () {
  scheme = random(4);

  frst_color.set(schemes[scheme][0].get(dim));
  scnd_color.set(schemes[scheme][2].get(dim));
  thrd_color.set(schemes[scheme][4].get(dim));
}

RGB random_color () {
  return schemes[scheme][random(5)].get(dim);
}


// red: { 255, 48, 48 }
// coral: { 255, 90, 75 }
// salmon: { 255, 135, 75 }
// orange: { 120, 25, 2 }
// yellow: { 153, 99, 28 }
// creme: { 138, 70, 45 }
// dark yellow: {168, 102, 22}
