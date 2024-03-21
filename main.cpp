#include "mux.h"
#include "dispatcher.h"
#include "arbiter.h"
#include "demux.h"
#include <vector>
#include <functional>
#include <fstream>

// FIXME: Need to add CPU, RAM

void cpuLoad(std::string fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "cpuLoad error\n";
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    // push line to code segment
  }

  file.close();
}

void BusRunner() {
  /// fifo for dispatcher 0
  DISPATCHER<int> dis0(&cpu02dis0, &dis02arb0, &dis02arb1, &dis02mux0),
      dis1(&cpu12dis1, &dis12arb0, &dis12arb1, &dis12mux1); /// check dis12arb0, dis12arb1 order here

  ARBITER<int> arb0(&dis02arb0, &dis12arb0, &arb02demux0, &arb02ram0),
      arb1(&dis02arb1, &dis12arb1, &arb12demux1, &arb12vga1);

  MUX<int> mux0(&mux02cpu0, &demux02mux0, &demux12mux0, &dis02mux0),
      mux1(&mux12cpu1, &demux02mux1, &demux12mux1, &dis12mux1);

  DEMUX<int> demux0(&ram02demux0, &arb02demux0, &demux02mux0, &demux02mux1),
      demux1(&vga2demux1, &arb12demux1, &demux12mux0, &demux12mux1);

  std::vector <std::function<void()>> tasks =
      {[&] { dis0.runDispatcher();}, [&] { dis1.runDispatcher();}, [&] { arb0.runArbiter();}, [&] {arb1.runArbiter();},
       [&] {mux0.runMux();}, [&] {mux1.runMux();},
       [&] {demux0.runDemux();}, [&] {demux1.runDemux();}};

  while (true) {
    for (auto &task : tasks) {
      task();
    }

    break;
  }
}

int main() {
  BusRunner();
  return 0;
}
