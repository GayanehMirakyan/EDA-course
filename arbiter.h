#ifndef ARBITER_H
#define ARBITER_H
#include <array>
#include "Fifo.h"

template<class data_width>
void runArbiter(Fifo<8, data_width> fifo) {
  while (true) {
    if (!fifo.check_empty()) {
      auto fifoElem = fifo.pop();
      if (fifoElem[MODE] == WRITE) {
        /// send data to ram
        break;
      } else if (fifoElem[MODE] == READ) {
        break;
      }
    }
  }
}

#endif  // ARBITER_H