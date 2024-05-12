template <typename T> 
struct RingBuffer { 
  int pointer=0;
  void * callback;
  T values [16];
  void write (T el) {
    T old_el = values[pointer];
    if (old_el!=NULL) calback(old_el);
    values[pointer] = el;
    pointer = (pointer+1)%8;
  }
}; 
