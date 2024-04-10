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

  std::unordered_map<std::string, int> instructionMap = {
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
    if (instructionMap.find(line) != instructionMap.end()) {
      instructionArray.push_back(instructionMap[line]);
    } else {
      std::istringstream iss(line);
      int num;
      iss >> num;
      if(iss.eof() && !iss.fail()) {
        instructionArray.push_back(num);

      } else {
        std::cerr << "Unknown instruction: " << line << std::endl;
      }
    }
  }

  file.close();
}
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::vector<int> instructionArray;
  loadFile(argv[1], instructionArray);

  /// need to write data from file to ram
  cpu.loadToRam(instructionArray);
  ram.print_memory();

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
