#ifndef FIFO_H
#define FIFO_H

#include <array>
#include <iostream>

enum Instructions {
    PUSH,
    ADD,
    DIV,
    MUL,
    INV,
    LOAD,
    STORE,
    SAVEPC,
    JMP,
    CJMP,
    GREAT,
    DUP,
    OVER,
    SWAP,
    HALT,
    PRINT
};

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
  RAM_MAX = 256,
  VGA_MIN = 257,
  VGA_MAX = 500
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
  void push_all(data_width mode, data_width address, data_width data);
  std::array<data_width, 3> pop_all();

  data_width pop();

//private:
  std::array<data_width, 3> fifo;
  int write_ptr;
  int read_ptr;
  bool full;
  bool empty;
  data_width data_out;
  int count;
};

template<int depth, class data_width>
Fifo<depth, data_width>::Fifo() : write_ptr(0), read_ptr(0), full(false), empty(true), count(0) {}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_empty() {
  return count == 0;
}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_full() {
  return count == 3;
}

template<int depth, class data_width>
data_width Fifo<depth, data_width>::get_data_out() const {
  return data_out;
}

template<int depth, class data_width>
void Fifo<depth, data_width>::push_all(data_width mode, data_width address, data_width data) {
  this->push(mode);
  this->push(address);
  this->push(data);
}

template<int depth, class data_width>
std::array<data_width, 3> Fifo<depth, data_width>::pop_all() {
  data_width Data = this->pop();
  data_width Address = this->pop();
  data_width Mode = this->pop();
  return {Mode, Address, Data};
}

template<int depth, class data_width>
void Fifo<depth, data_width>::push(data_width data) {
  if (count >= 3) {
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
Fifo<8, int> ram02demux0;
Fifo<8, int> arb02ram0;


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
