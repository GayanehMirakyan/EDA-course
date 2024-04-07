#ifndef CPU_H
#define CPU_H

#include <array>
#include "Fifo.h"
#include "ram.h"
#include "bus.h"

enum Instructions {
  PUSH,
  ADD,
  DIV,
  MUL,
  INV,
  LOAD,
  STORE,
  SAVEPC,
  JMP,
  CJMP,
  GREAT,
  DUP,
  OVER,
  SWAP,
  HALT,
  PRINT
};

class CPU {
public:

  CPU(Fifo<8, int> *cpu2dis,
      Fifo<8, int> *mux2cpu
  ) : cpu2dis(cpu2dis), mux2cpu(mux2cpu), prev_push(false) {
    // TODO change
  }

  int code_pointer = CODE_SEGMENT_MIN;
  int stack_pointer = STACK_SEGMENT_MIN;
  int data_pointer = DATA_SEGMENT_MIN;
  bool prev_push;

  void runCpu();

  void push(int Data);

  int pop();

  void add();

  void startCPU(int address);

  Fifo<8, int> *cpu2dis;
  Fifo<8, int> *mux2cpu;

};

void CPU::startCPU(int address) {
  cpu2dis->push_all(READ, address, 0);

}

void CPU::push(int Data) {
  std::cout << "is PUSH inst\n";
  cpu2dis->push_all(WRITE, stack_pointer, Data);
  bus.runSendToRam();
  stack_pointer++;
//  code_pointer++;
}

int CPU::pop() {
  if (stack_pointer == 0)
    return -1;
  stack_pointer--;
  cpu2dis->push_all(READ, stack_pointer, 0);

  bus.runSendToRam();
  ram.runRam();
  if (mux2cpu->check_empty())
    return INT32_MIN;
  auto getData = mux2cpu->pop_all();

  return getData[DATA];
}

void CPU::add() {
  int temp1 = pop();
  int temp2 = pop();

  std::cout << temp1 << "     " << temp2 << "\n";
  push(temp1 + temp2);
}

void CPU::runCpu() {
  if (code_pointer < CODE_SEGMENT_MAX && stack_pointer < STACK_SEGMENT_MAX) {

    if (!mux2cpu->check_empty()) {
      std::cout << "in CPU: mux to cpu fifo is not empty\n";
      int Data = mux2cpu->pop();
      int Address = mux2cpu->pop();
      int Mode = mux2cpu->pop();
//    if (Mode == WRITE) {
      /// check which instruction is
      if (prev_push) {
        std::cout << "prev_push is true\n";
        push(Data);
        prev_push = false;
        return;
      }

      switch (Data) {
      case PUSH:std::cout << "push\n";
        prev_push = true;
        code_pointer = Address;
//          cpu2dis->push_all(READ, code_pointer, Data);
        startCPU(code_pointer);
        break;
      case ADD:std::cout << "add\n";
        add();
        break;
      }
      //      std::cerr << "runCpu write \n" << Data << "\n";
//    }
//    else if (Mode == READ) {
//      std::cerr << "runCpu read \n";
//
//    }
      code_pointer++;

    } else {
      startCPU(code_pointer);
//      code_pointer++;

//      cpu2dis->push_all(READ, code_pointer, 0);
    }

  }
}

#endif // CPU_H