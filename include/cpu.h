#ifndef CPU_H
#define CPU_H
#include <array>
#include "Fifo.h"
#include "ram.h"

enum Instructions {
  PUSH,
  POP,
  ADD,
  DIV
};

class CPU {
public:

  CPU(Fifo<8, int> *cpu2dis,
      Fifo<8, int> *mux2cpu
  ) : cpu2dis(cpu2dis), mux2cpu(mux2cpu), prev_push(false), prev_pop(false) {
    // TODO change
    cpu2dis->push_all(READ, 0, 0);

  }

  int code_pointer = CODE_SEGMENT_MIN;
  int stack_pointer = STACK_SEGMENT_MIN;
  int data_pointer = DATA_SEGMENT_MIN;
  bool prev_push;
  bool prev_pop;

  void runCpu();
  void push(int Data);
  int pop();
  void add();

  Fifo<8, int> *cpu2dis;
  Fifo<8, int> *mux2cpu;

};

void CPU::push(int Data) {
  std::cout << "is PUSH inst\n";
  cpu2dis->push_all(WRITE, stack_pointer, Data);
  stack_pointer++;
  code_pointer++;
}

int CPU::pop() {
  if (stack_pointer == 0)
    return -1;

  code_pointer++;
  stack_pointer--;
  cpu2dis->push_all(READ, stack_pointer, 0);
//  return
}

void CPU::add() {

//  int a = pop();

}

void CPU::runCpu() {
  if(code_pointer < CODE_SEGMENT_MAX && stack_pointer < STACK_SEGMENT_MAX) {

    if (!mux2cpu->check_empty() ) {
      std::cout << "in CPU: mux to cpu fifo is not empty\n";
      int Data = mux2cpu->pop();
      int Address = mux2cpu->pop();
      int Mode = mux2cpu->pop();
//    bool prev_push = false;
//    if (Mode == WRITE) {
      /// check which instruction is
      if (prev_push) {
        std::cout << "prev_push is true\n";
        push(Data);
        prev_push = false;
      }
      if (prev_pop) {

        prev_pop = false;
      }
      switch (Data) {
      case PUSH: std::cout << "push\n";
        prev_push = true;
        Address++;
        code_pointer = Address;
        cpu2dis->push_all(READ, code_pointer, Data);

        break;
      case POP: std::cout << "pop\n";
      prev_pop = true;
        pop();
        break;
      case ADD: std::cout << "add\n";
        break;
      }
      //      std::cerr << "runCpu write \n" << Data << "\n";
//    }
//    else if (Mode == READ) {
//      std::cerr << "runCpu read \n";
//
//    }

    } else if(all_fifo_empty()) {
//      code_pointer++;
      cpu2dis->push_all(READ, code_pointer, 0);
    }

  }
}

#endif // CPU_H