#ifndef RAM_H
#define RAM_H

#include <array>
#include <iostream>
#include "Fifo.h"
#include <vector>
#include <functional>
#include <fstream>

enum ram_address {
  CODE_SEGMENT_MIN = 0,
  CODE_SEGMENT_MAX = 85,
  STACK_SEGMENT_MIN = 86,
  STACK_SEGMENT_MAX = 171,
  DATA_SEGMENT_MIN = 172,
  DATA_SEGMENT_MAX = 256,
};

#define RAM_SIZE ram_address::DATA_SEGMENT_MAX

class RAM {
public:
  RAM(Fifo<8, int> *arb2ram,
      Fifo<8, int> *ram2demux
  ) : arb2ram(arb2ram),
      ram2demux(ram2demux) {
    for (int i = 0; i < RAM_SIZE; i++) {
      memory[i] = -1;
    }

    memory[0] = PUSH;
    memory[1] = 10;
    memory[2] = PUSH;
    memory[3] = 6;
    memory[4] = ADD;
    memory[5] = PUSH;
    memory[6] = 4;
    memory[7] = ADD;
    memory[8] = PUSH;
    memory[9] = 4;
    memory[10] = PUSH;
    memory[11] = 4;
    memory[12] = ADD;
    memory[13] = ADD;
    memory[14] = INV;


  }

  Fifo<8, int> *arb2ram;
  Fifo<8, int> *ram2demux;
  std::array<int, RAM_SIZE> memory; // TODO initialize with 0

  void print_memory();

  void runRam();
};

void RAM::print_memory() {
  for (auto elem: memory) {
    std::cerr << elem << "\n";
  }
}



void cpuLoad(std::string fileName, std::vector<Instructions>& instructionArray) {
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
    if (instructionMap.find(line) != instructionMap.end()) {
      instructionArray.push_back(instructionMap[line]);
    } else {
      std::cerr << "Unknown instruction: " << line << std::endl;
    }
  }

  file.close();
}

void RAM::runRam() {

  if (!arb2ram->check_empty()) {

    std::cout << " RAM \n";
    auto from_fifo = arb2ram->pop_all();;
    int Mode = from_fifo[MODE];
    int Address = from_fifo[ADDRESS];
    int Data = from_fifo[DATA];
    std::cout << " arb to ram fifo \n";
    std::cerr << "Mode = " << Mode << "   Address = " << Address << "   Data = " << Data << "\n";

    if (Mode == READ) {
      /// ram to demux
//      std::cout << memory[Address] << "\n" << ram2demux->check_empty() << "\n";
      if (Address <= STACK_SEGMENT_MAX && Address >= STACK_SEGMENT_MIN) {
        ram2demux->push_all(Mode, Address, memory[Address]);
        memory[Address] = -1;
      } else if (Address <= CODE_SEGMENT_MAX && Address >= CODE_SEGMENT_MIN) {
        ram2demux->push_all(Mode, Address, memory[Address]);
      }
      std::cout << "after push to ram2demux\n";
    } else {
      /// WRITE
      std::cout << "write to ram " << Data << "\n";
      memory[Address] = Data;

    }
  }
}

RAM ram(&arb02ram0, &ram02demux0); // FIXME : arb02ram0 --> arb02ram

#endif //RAM_H
