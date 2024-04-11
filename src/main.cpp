#include "mux.h"
#include "dispatcher.h"
#include "demux.h"
#include "cpu.h"
#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>

CPU cpu(&cpu02dis0, &mux02cpu0);

void loadFile(std::string fileName, std::vector<int> &instructionArray) {
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "File loading error\n";
    return;
  }

  std::unordered_map<std::string, int> instructionMap = {
      {"PUSH",   PUSH},
      {"ADD",    ADD},
      {"DIV",    DIV},
      {"MUL",    MUL},
      {"INV",    INV},
      {"LOAD",   LOAD},
      {"STORE",  STORE},
      {"SAVEPC", SAVEPC},
      {"JMP",    JMP},
      {"CJMP",   CJMP},
      {"GREAT",  GREAT},
      {"DUP",    DUP},
      {"OVER",   OVER},
      {"SWAP",   SWAP},
      {"HALT",   HALT},
      {"PRINT",  PRINT}
  };

  std::string line;
  while (std::getline(file, line)) {
    if (instructionMap.find(line) != instructionMap.end()) {
      instructionArray.push_back(instructionMap[line]);
    } else {
      std::istringstream iss(line);
      int num;
      iss >> num;
      if (iss.eof() && !iss.fail()) {
        instructionArray.push_back(num);

      } else {
        std::cerr << "Unknown instruction: " << line << std::endl;
      }
    }
  }

  file.close();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::vector<int> instructionArray;
  loadFile(argv[1], instructionArray);

  /// need to write data from file to ram
  cpu.loadToRam(instructionArray);

  std::vector<std::function<void()>> tasks =
      {[&] { cpu.runCpu(); },
       [&] { bus.runSendToRam(); }, [&] { ram.runRam(); }, [&] { bus.runSendToCpu(); }};
  while (true) {
    for (auto &task: tasks) {
      task();
    }
    if (cpu.off) {
      break;
    }
/// for debug
//    cpu.runCpu();
//    bus.runSendToRam();
//    ram.runRam();
//    bus.runSendToCpu();
  }
  return 0;
}
