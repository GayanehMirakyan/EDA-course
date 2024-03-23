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

enum address { // TODO ram and vga are different classes
  RAM_MIN = 0,
  RAM_MAX = 25,
  VGA_MIN = 26,
  VGA_MAX = 50
};

template<int depth, class data_width>
class Fifo {
public:
  Fifo();

//  void step(bool reset, bool write, bool read, data_width data_in = 0);

  bool check_empty();

  bool check_full();

  bool write;

  bool read;

  data_width get_data_out() const;

  void push(data_width data);

  data_width pop();

private:
  std::array <data_width, depth*3> fifo;
  int write_ptr;
  int read_ptr;
  bool full;
  bool empty;
  data_width data_out;
  int count;
};


template<int depth, class data_width>
Fifo<depth, data_width>::Fifo() : write_ptr(0), read_ptr(0), full(false), empty(true), count(0) {}

//template<int depth, class data_width>
//void Fifo<depth, data_width>::step(bool reset, bool write, bool read, data_width data_in) {
//  if (reset) {
//    write_ptr = 0;
//    read_ptr = 0;
//    data_out = 0;
//    full = false;
//    empty = true;
//  } else {
//    empty = check_empty();
//    full = check_full();
//    if (write && !full) {
//      push(data_in);
//    } else if (read && !empty) {
//      pop();
//    }
//  }
//}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_empty() {
  return count == 0;
}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_full() {
  return count == 7;
}

template<int depth, class data_width>
data_width Fifo<depth, data_width>::get_data_out() const {
  return data_out;
}

template<int depth, class data_width>
void Fifo<depth, data_width>::push(data_width data) {
  if (count >= 8) {
    std::cout << "---Cannot push: Buffer Full---" << std::endl;
  } else {
    fifo[count] = data;

    count++;
    std::cout << "Pushed " << data << std::endl;
  }
}

template<int depth, class data_width>
data_width Fifo<depth, data_width>::pop() {
  data_width defArr = -1;
  if (fifo.empty()) {
    std::cout << "---Cannot Pop: Buffer Empty---" << std::endl;
    return defArr;
  }
  /// [mode, address, data]
  data_width data = fifo[count - 1];
  count--;
  std::cout << "-------------------------------Poped " << data << std::endl;
  return data;
}


Fifo<8, int> cpu02dis0;
Fifo<8, int> mux02cpu0;
Fifo<8, int> dis02arb0;
Fifo<8, int> dis02arb1;
Fifo<8, int> dis02mux0;
Fifo<8, int> arb02ram0;
Fifo<8, int> arb02demux0;
Fifo<8, int> ram02demux0;
Fifo<8, int> demux02mux0;
Fifo<8, int> demux02mux1;

Fifo<8, int> demux12mux0;
Fifo<8, int> demux12mux1;
Fifo<8, int> mux12cpu1;
Fifo<8, int> vga2demux1;
Fifo<8, int> arb12demux1;
Fifo<8, int> arb12vga1;
Fifo<8, int> dis12arb1;
Fifo<8, int> dis12mux1;
Fifo<8, int> dis12arb0;
Fifo<8, int> cpu12dis1;


#endif // FIFO_H
