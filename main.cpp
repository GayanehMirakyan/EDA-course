#include "mux.h"
#include "dispatcher.h"
#include "arbiter.h"
#include "demux.h"


void BusRunner() {
  /// fifo for dispatcher 0
  DISPATCHER<int> dis0(cpu02dis0, dis02arb0, dis02arb1, dis02mux0),
      dis1(cpu12dis1, dis12arb0, dis12arb1, dis12mux1); /// check dis12arb0, dis12arb1 order here
  ARBITER<int> arb0, arb1;
  MUX<int> mux0, mux1;
  DEMUX<int> demux0, demux1;
  std::vector <std::function<void()>> tasks =
      {dis0.runDispatcher(), dis1.runDispatcher(), arb0.runArbiter(), arb1.runArbiter(), mux0.runMux(), mux1.runMux(),
       demux0.runDemux(), demux1.runDemux()};

  while (true) {
    for(auto& task : tasks) {
      task();
    }

    break;
  }
}

int main() {
//  fifo_test();

  BusRunner();
  return 0;
}
