#include "mux.h"
#include "dispatcher.h"
#include "arbiter.h"
#include "demux.h"
#include "cpu.h"
#include "bus.h"
#include "ram.h"
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>


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

CPU cpu(&cpu02dis0, &mux02cpu0);
RAM ram(&arb02ram0, &ram02demux0); // FIXME : arb02ram0 --> arb02ram

int main() {
//  ram.print_memory();


  std::vector<std::function<void()>> tasks =
          {[&] { cpu.runCpu(); },
           [&] { bus.runSendToRam(); }, [&] { ram.runRam(); }, [&] { bus.runSendToCpu(); }};
  int i = 0;
  while (true) {
    for (auto &task: tasks) {

      task();
    }
    i++;
    if (i > 100) {
      break;
    }

  }
  ram.print_memory();
  return 0;
}
