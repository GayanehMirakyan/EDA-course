#ifndef RAM_H
#define RAM_H

#include <array>
#include <iostream>
#include "Fifo.h"
#include <vector>
#include <functional>
#include <fstream>

enum ram_address {
  CODE_SEGMENT_MIN = 0,
  CODE_SEGMENT_MAX = 85,
  STACK_SEGMENT_MIN = 86,
  STACK_SEGMENT_MAX = 171,
  DATA_SEGMENT_MIN = 172,
  DATA_SEGMENT_MAX = 256,
};

#define RAM_SIZE ram_address::DATA_SEGMENT_MAX

class RAM {
public:
  RAM(Fifo<8, int> *arb2ram,
      Fifo<8, int> *ram2demux
  ) : arb2ram(arb2ram),
      ram2demux(ram2demux) {
    for (int i = 0; i < RAM_SIZE; i++) {
      memory[i] = INT16_MIN;
    }
  }

  Fifo<8, int> *arb2ram;
  Fifo<8, int> *ram2demux;
  std::array<int, RAM_SIZE> memory;

  void print_memory();

  void runRam();
};

void RAM::print_memory() {
  for (int st = STACK_SEGMENT_MIN; st <= STACK_SEGMENT_MAX; st++) {
    std::cerr << memory[st] << " ";
  }
  std::cerr << "\n";

}

void RAM::runRam() {

  if (!arb2ram->check_empty()) {

    auto from_fifo = arb2ram->pop_all();;
    int Mode = from_fifo[MODE];
    int Address = from_fifo[ADDRESS];
    int Data = from_fifo[DATA];

    if (Mode == READ) {
      /// ram to demux
      if (Address <= STACK_SEGMENT_MAX && Address >= STACK_SEGMENT_MIN) {
        ram2demux->push_all(Mode, Address, memory[Address]);
        memory[Address] = -1;
      } else if (Address <= CODE_SEGMENT_MAX && Address >= CODE_SEGMENT_MIN) {
        ram2demux->push_all(Mode, Address, memory[Address]);
      } else if (Address <= DATA_SEGMENT_MAX && Address >= DATA_SEGMENT_MIN) {
        ram2demux->push_all(Mode, Address, memory[Address]);

      }
    } else {
      /// WRITE
      memory[Address] = Data;

    }
  }
}

RAM ram(&arb02ram, &ram02demux0);

#endif //RAM_H
