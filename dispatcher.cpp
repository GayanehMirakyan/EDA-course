#include "dispatcher.h"

template<class data_width>
void runDispatcher(Fifo<8, data_width> fifo) {
  while (true) {
    if (!fifo.check_empty()) {
      std::array<int, 3> elem = fifo.pop();
      if (elem[MODE] == WRITE) {
        /// call arbiter0 or arbiter1
        /// depends on address range

        Fifo<8, int> fifo_arbiter_0;
        fifo_arbiter_0.push(elem);

        runArbiter(fifo_arbiter_0);
        break;
      } else {
        /// mode is read
        break;
      }
    }
  }

}
template void runDispatcher<int>(Fifo<8, int> fifo);