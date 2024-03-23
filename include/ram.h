#ifndef RAM_H
#define RAM_H
#include <array>
#include <iostream>
#include "Fifo.h"

enum ram_address {
  CODE_SEGMENT_MIN = 0,
  CODE_SEGMENT_MAX = 25,
  STACK_SEGMENT_MIN = 26,
  STACK_SEGMENT_MAX = 50,
  DATA_SEGMENT_MIN = 51,
  DATA_SEGMENT_MAX = 75,
};

#define RAM_SIZE ram_address::DATA_SEGMENT_MAX


class RAM {
public:
  RAM(Fifo<8, int> *arb2ram,
      Fifo<8, int> *ram2demux) : arb2ram(arb2ram), ram2demux(ram2demux) {}

  Fifo<8, int> *arb2ram;
  Fifo<8, int> *ram2demux;
  std::array <int, RAM_SIZE> memory; // TODO initialize with 0

  void print_memory();
};

void RAM::print_memory() {
  for (auto elem : memory) {
    std::cerr << elem << "\n";
  }
}

#endif //RAM_H
