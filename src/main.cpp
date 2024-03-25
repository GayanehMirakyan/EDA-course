#include "mux.h"
#include "dispatcher.h"
#include "arbiter.h"
#include "demux.h"
#include "cpu.h"
#include "ram.h"
#include <iostream>
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
    // push line to code segment via cpu load instruction
  }

  file.close();
}

void BusRunner() {
  /// fifo for dispatcher 0
  CPU cpu(&cpu02dis0, &mux02cpu0);
  RAM ram(&arb02ram0, &ram02demux0); // FIXME : arb02ram0 --> arb02ram
//std::cerr << "after ram " << ram.arb2ram << "\n";
  DISPATCHER<int> dis0(&cpu02dis0, &dis02arb0, &dis02arb1, &dis02mux0);
//      dis1(&cpu12dis1, &dis12arb0, &dis12arb1, &dis12mux1); /// check dis12arb0, dis12arb1 order here

  ARBITER<int> arb0(&dis02arb0, &dis12arb0, &arb02demux0, &arb02ram0);
//      arb1(&dis02arb1, &dis12arb1, &arb12demux1, &arb12vga1);

  std::cerr << "after arb " << arb0.arb2ram << "\n";
  MUX<int> mux0(&mux02cpu0, &demux02mux0, &demux12mux0, &dis02mux0);
//      mux1(&mux12cpu1, &demux02mux1, &demux12mux1, &dis12mux1);

  DEMUX<int> demux0(&ram02demux0, &arb02demux0, &demux02mux0, &demux02mux1);
//      demux1(&vga2demux1, &arb12demux1, &demux12mux0, &demux12mux1);

  std::vector <std::function<void()>> tasks =
      {[&] { dis0.runDispatcher();},  [&] { arb0.runArbiter();},
       [&] {mux0.runMux();},
       [&] {demux0.runDemux();}, [&]{ram.runRam();}, [&]{cpu.runCpu();}};
int i = 0;
  while (true) {
    for (auto &task : tasks) {

//      std::cout << "arb2ram in whl before: " << arb0.arb2ram << "\n"; // arden chpacaca
      task();
    }
    i++;
    if (i > 20) {
      break;
    }

//    if(mux02cpu0.check_full()) {
//      break;
//    }
  }
  ram.print_memory();

}

int main() {
//  ram.print_memory();
  BusRunner();
  return 0;
}
