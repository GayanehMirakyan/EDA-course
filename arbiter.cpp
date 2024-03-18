#include "arbiter.h"

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

template void runArbiter<int>(Fifo<8, int> fifo);
