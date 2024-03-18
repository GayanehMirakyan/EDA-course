#ifndef FIFO_H
#define FIFO_H

#include <array>
#include <iostream>

enum {
  MODE,
  ADDRESS,
  DATA
};

enum mode {
  READ,
  WRITE
};

enum address {
  CPU_MIN = 0,
  CPU_MAX = 25,
  VGA_MIN = 26,
  VGA_MAX = 50
};

template<int depth, class data_width>
class Fifo {
public:
  Fifo();

  void step(bool reset, bool write, bool read, data_width data_in = 0);

  bool check_empty();

  bool check_full();

  bool write;

  bool read;

  data_width get_data_out() const;

  void push(data_width data);

  data_width pop();

private:
  std::array <std::array<data_width, 3>, depth> fifo;
  int write_ptr;
  int read_ptr;
  bool full;
  bool empty;
  data_width data_out;
  int count;
};

#endif // FIFO_H
