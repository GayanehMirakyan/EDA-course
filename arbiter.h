#ifndef ARBITER_H
#define ARBITER_H
#include <array>
#include "Fifo.h"

template<class data_width>
class ARBITER {
public:
  ARBITER(Fifo<8, int> *dis02arb,
          Fifo<8, int> *dis12arb,
          Fifo<8, int> *arb2demux,
          Fifo<8, int> *arb2ram) : dis02arb(dis02arb), dis12arb(dis12arb), arb2demux(arb2demux), arb2ram(arb2ram) {}

  Fifo<8, int> *dis02arb;
  Fifo<8, int> *dis12arb;
  Fifo<8, int> *arb2demux;
  Fifo<8, int> *arb2ram;

  void runArbiter();
};

template<class data_width>
void ARBITER<data_width>::runArbiter() {
  if (!dis02arb->check_empty()) {

    data_width Data = arb2demux->pop();
    data_width Address = arb2demux->pop();
    data_width Mode = arb2demux->pop();

    if (Mode == WRITE) {
      /// send data to ram
    } else if (Mode == READ) {

    }
  }
}

#endif  // ARBITER_H