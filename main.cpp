#include "mux.h"
#include "dispatcher.h"
#include "arbiter.h"

//void fifo_test() {
//  Fifo<8, int> fifo;
//
//  for (int i = 0; i < 15; i++) {
//    fifo.step(false, true, false, 1); // Write 1
//    fifo.step(false, true, false, 2); // Write 2
//    fifo.step(false, false, true); // Read
//    // fifo.step(false, true, false, i); // Write i
//    // fifo.step(false, true, false, i); // Write i
//  }
//  fifo.step(true, false, false); // Reset
//
//
//  // std::cout << "Is empty: " << fifo.check_empty() << std::endl;
//  // std::cout << "Is full: " << fifo.check_full() << std::endl;
//  // std::cout << "Data out: " << fifo.get_data_out() << std::endl;
//}

void BusRunner() {
  /// fifo for dispatcher 0
  Fifo<8, int> fifo_dispatcher_0;

  while (true) {
    /// need to load instructions from file

    fifo_dispatcher_0.push({1, 1, 1});

    /// call dispatcher
    runDispatcher(fifo_dispatcher_0);

    break;
  }

  Fifo<8, int> fifo_a;
  fifo_a.push({1, 1, 1});
  Fifo<8, int> fifo_b;
  fifo_b.push({0, 2, 12});
  Fifo<8, int> fifo_c;
  fifo_c.push({1, 3, 44});
  Fifo<8, int> fifo_out;
  Fifo<8, int> fifo_select;
  fifo_select.push({0, 0, 0});

  mux::runMux(fifo_select, fifo_a, fifo_b, fifo_c, fifo_out);
}

int main() {
//  fifo_test();

  BusRunner();
  return 0;
}
