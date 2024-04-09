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

CPU cpu(&cpu02dis0, &mux02cpu0);

int main() {
//  ram.print_memory();


  std::vector<std::function<void()>> tasks =
          {[&] { cpu.runCpu(); },
           [&] { bus.runSendToRam(); }, [&] { ram.runRam(); }, [&] { bus.runSendToCpu(); }};
  int i = 0;
  while (true) {
//    for (auto &task: tasks) {
//
//      task();
//    }

    cpu.runCpu();
    bus.runSendToRam();
    ram.runRam();
    bus.runSendToCpu();

    i++;
    if (i > 100) {
      break;
    }

  }
  ram.print_memory();
  return 0;
}
