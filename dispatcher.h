#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <array>
#include "Fifo.h"
#include "mux.h"
#include "arbiter.h"

template<class data_width>
class DISPATCHER {
public:

  DISPATCHER(Fifo<8, data_width> *cpu2dis,
             Fifo<8, data_width> *dis2arb0,
             Fifo<8, data_width> *dis2arb1,
             Fifo<8, data_width> *dis2mux) : cpu2dis(cpu2dis), dis2arb0(dis2arb0), dis2arb1(dis2arb1), dis2mux(dis2mux)
             {}

  void runDispatcher();

  Fifo<8, data_width> *cpu2dis;
  Fifo<8, data_width> *dis2arb0;
  Fifo<8, data_width> *dis2arb1;
  Fifo<8, data_width> *dis2mux;
};

template<class data_width>
void DISPATCHER::runDispatcher() {
  while (true) {
    if (!cpu2dis.check_empty()) {
      std::array<int, 3> elem = cpu2dis->pop();
      if (elem[MODE] == WRITE) {
        /// call arbiter0 or arbiter1
        /// depends on address range

/// fix fifo element
/// do push 3 time
        dis2arb0->push(elem);
        break;
      } else {
        /// mode is read
        break;
      }
    }
  }
}
#endif // DISPATCHER_H