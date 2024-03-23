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

    data_width Data = dis02arb->pop();
    data_width Address = dis02arb->pop();
    data_width Mode = dis02arb->pop();

    if (Mode == WRITE) {
      /// send data to ram
      arb2ram->push(Data);
      arb2ram->push(Address);
      arb2ram->push(Mode);
    } else if (Mode == READ) {
      arb2demux->push(0); // ?
      arb2demux->push(Address); // ?
      arb2demux->push(mode::WRITE); // no. of cpu
    }
  } // else if or if???
  if (!dis12arb->check_empty()) {

    data_width Data = dis12arb->pop();
    data_width Address = dis12arb->pop();
    data_width Mode = dis12arb->pop();

    if (Mode == WRITE) {
      /// send data to ram
      arb2ram->push(Data);
      arb2ram->push(Address);
      arb2ram->push(Mode);
    } else if (Mode == READ) {
      arb2demux->push(1); // ?
      arb2demux->push(Address); // ?
      arb2demux->push(mode::WRITE); // no. of cpu
    }
  }
}

#endif  // ARBITER_H