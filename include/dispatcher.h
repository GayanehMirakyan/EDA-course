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
             Fifo<8, data_width> *dis2mux)
      : cpu2dis(cpu2dis), dis2arb0(dis2arb0), dis2arb1(dis2arb1), dis2mux(dis2mux) {}

  void runDispatcher();

  Fifo<8, data_width> *cpu2dis;
  Fifo<8, data_width> *dis2arb0;
  Fifo<8, data_width> *dis2arb1;
  Fifo<8, data_width> *dis2mux;
};

template<class data_width>
void DISPATCHER<data_width>::runDispatcher() {
  if (!cpu2dis->check_empty()) {
    auto from_fifo = cpu2dis->pop_all();;
    data_width Mode = from_fifo[MODE];
    data_width Address = from_fifo[ADDRESS];
    data_width Data = from_fifo[DATA];

    if (Mode == WRITE) {
      /// CHOOSE ARBITER ACCORDING TO THE ADDRESS
      /// call arbiter0 or arbiter1
      /// depends on address range
      if (Address <= address::RAM_MAX) {
        dis2arb0->push_all(Mode, Address, Data);

      } else {
        /// here is vga
        dis2arb1->push_all(Mode, Address, Data);
      }

    } else {
      /// mode is READ
      if (Address <= address::RAM_MAX) {
        /// for mux selector
        dis2mux->push_all(Mode, Address, 0);

        dis2arb0->push_all(Mode, Address, Data);
      } else {
        /// for mux selector
        dis2mux->push_all(Mode, Address, 1);

        dis2arb1->push_all(Mode, Address, Data);
      }
    }
  }
}

#endif // DISPATCHER_H