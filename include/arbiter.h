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
          Fifo<8, int> *arb2ram
          ) : dis02arb(dis02arb), dis12arb(dis12arb), arb2demux(arb2demux), arb2ram(arb2ram) {}

  Fifo<8, int> *dis02arb;
  Fifo<8, int> *dis12arb;
  Fifo<8, int> *arb2demux;
  Fifo<8, int> *arb2ram;

  void runArbiter();
};

template<class data_width>
void ARBITER<data_width>::runArbiter() {
//  std::cout << "arb2ram in arb before: " << arb2ram << "\n"; // arden chpacaca
  if (!dis02arb->check_empty()) {
    std::cout << " ARBITER \n";

    std::cout << "get data from dispatcher0\n";
    auto from_fifo = dis02arb->pop_all();;
    data_width Mode = from_fifo[MODE];
    data_width Address = from_fifo[ADDRESS];
    data_width Data = from_fifo[DATA];

    if (Mode == WRITE) {
      /// send data to ram
      std::cout << "WRITE to Ram\n";
      std::cerr << "Mode = " << Mode << "   Address = " << Address << "   Data = " << Data << "\n";

      arb2ram->push_all(Mode, Address, Data);
    } else if (Mode == READ) {
      /// read
      std::cout << "need to READ from Ram\n";
      arb2demux->push_all(Mode, Address, 0);
      arb02ram0.push_all(Mode, Address, Data);

    }
  }
  else if (!dis12arb->check_empty()) {
    std::cout << " ARBITER \n";

    std::cout << "get data from dispatcher1\n";
    auto from_fifo = dis12arb->pop_all();;
    data_width Mode = from_fifo[MODE];
    data_width Address = from_fifo[ADDRESS];
    data_width Data = from_fifo[DATA];

    if (Mode == WRITE) {
      /// send data to ram
      std::cout << "WRITE to Ram\n";
      arb2ram->push_all(Mode, Address, Data);


    } else if (Mode == READ) {
      arb2demux->push_all(Mode, Address, 0);
      arb02ram0.push_all(Mode, Address, Data);

    }
  }
}

#endif  // ARBITER_H