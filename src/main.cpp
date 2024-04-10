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
#include <sstream>

CPU cpu(&cpu02dis0, &mux02cpu0);
void loadFile(std::string fileName, std::vector<int>& instructionArray) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "cpuLoad error\n";
    return;
  }

  std::unordered_map<std::string, Instructions> instructionMap = {
      {"PUSH", PUSH},
      {"ADD", ADD},
      {"DIV", DIV},
      {"MUL", MUL},
      {"INV", INV},
      {"LOAD", LOAD},
      {"STORE", STORE},
      {"SAVEPC", SAVEPC},
      {"JMP", JMP},
      {"CJMP", CJMP},
      {"GREAT", GREAT},
      {"DUP", DUP},
      {"OVER", OVER},
      {"SWAP", SWAP},
      {"HALT", HALT},
      {"PRINT", PRINT}
  };

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string instruction;
    int number;
    iss >> instruction;
    if (instructionMap.find(instruction) != instructionMap.end()) {
      instructionArray.push_back(instructionMap[instruction]);
      if (iss >> number) {
        instructionArray.push_back(number);
      }
    } else {
      std::cerr << "Unknown instruction: " << instruction << std::endl;
    }
  }

  file.close();
}
int main(int argc, char* argv[]) {
//  ram.print_memory();
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::vector<std::function<void()>> tasks =
          {[&] { cpu.runCpu(); },
           [&] { bus.runSendToRam(); }, [&] { ram.runRam(); }, [&] { bus.runSendToCpu(); }};
  int i = 0;
  while (true) {
//    for (auto &task: tasks) {
//      task();
//    }

/// for debug
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
