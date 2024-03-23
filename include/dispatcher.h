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
    data_width Mode = cpu2dis->pop();
    data_width Address = cpu2dis->pop();
    data_width Data = cpu2dis->pop();
    std::cerr << Mode << " " << Address << " "<< Data << "\n";

    if (Mode == WRITE) {
      /// CHOOSE ARBITER ACCORDING TO THE ADDRESS
      /// call arbiter0 or arbiter1
      /// depends on address range
      if (Address <= address::RAM_MAX) {
        dis2arb0->push(Data);
        dis2arb0->push(Address);
        dis2arb0->push(Mode);

      } else {
        /// here is vga
        dis2arb1->push(Data);
        dis2arb1->push(Address);
        dis2arb1->push(Mode);
      }

    } else {
      /// mode is read
      /// sent to mux selecter (no. of demux)
      if (Address <= address::RAM_MAX) {
        dis2mux->push(0); // data -- demux0
        dis2mux->push(Address); // adress ??
        dis2mux->push(mode::WRITE); // mode ??
      } else {        
        dis2mux->push(1); // data -- demux1
        dis2mux->push(Address); // adress ??
        dis2mux->push(mode::WRITE); // mode ??
      }
    }
  }
}
#endif // DISPATCHER_H