#ifndef CPU_H
#define CPU_H

#include <array>
#include "Fifo.h"
#include "ram.h"
#include "bus.h"

class CPU {
public:

  CPU(Fifo<8, int> *cpu2dis,
      Fifo<8, int> *mux2cpu
  ) : cpu2dis(cpu2dis), mux2cpu(mux2cpu), prev_push(false), off(false) {}

  int code_pointer = CODE_SEGMENT_MIN;
  int stack_pointer = STACK_SEGMENT_MIN;
  int data_pointer = DATA_SEGMENT_MIN;
  bool prev_push;
  bool off;

  void runCpu();

  int pop();

  void push(int Data);

  void add();

  void div();

  void store();

  void swap();

  int load();

  void savepc();

  void jmp();

  void cjmp();

  void inv();

  void mul();

  void grd();

  void dup();

  void over();

  void halt();

  void print();

  void startCPU(int address);

  void loadToRam(std::vector<int> instructionArray);

  Fifo<8, int> *cpu2dis;
  Fifo<8, int> *mux2cpu;

};

void CPU::loadToRam(std::vector<int> instructionArray) {
  for (auto elem : instructionArray) {
    cpu2dis->push_all(WRITE, code_pointer, elem);
    bus.runSendToRam();
    ram.runRam();
    code_pointer++;
  }
  /// set code pointer
  code_pointer = 0;
}

void CPU::startCPU(int address) {
  cpu2dis->push_all(READ, address, 0);

}

void CPU::push(int Data) {
  cpu2dis->push_all(WRITE, stack_pointer, Data);
  bus.runSendToRam();
  ram.runRam();
  stack_pointer++;
}

int CPU::pop() {
  if (stack_pointer == STACK_SEGMENT_MIN)
    return -1;
  stack_pointer--;
  cpu2dis->push_all(READ, stack_pointer, 0);

  bus.runSendToRam();
  ram.runRam();
  bus.runSendToCpu();
  if (mux2cpu->check_empty())
    return INT32_MIN;
  auto getData = mux2cpu->pop_all();

  return getData[DATA];
}

void CPU::add() {
  int temp1 = pop();
  int temp2 = pop();

  push(temp1 + temp2);
}

void CPU::store() {
  int address = pop();
  int data = pop();
  data_pointer = address;
  data_pointer++;
  cpu2dis->push_all(WRITE, address, data);
  bus.runSendToRam();
  ram.runRam();
}

int CPU::load() {
  int temp_addr = pop();
  cpu2dis->push_all(READ, temp_addr, 0);

  bus.runSendToRam();
  ram.runRam();
  bus.runSendToCpu();
  if (mux2cpu->check_empty())
    return INT32_MIN;
  auto getData = mux2cpu->pop_all();

  push(getData[DATA]);
  return getData[DATA];
}

void CPU::swap() {
  int temp1 = pop();
  int temp2 = pop();
  push(temp1);
  push(temp2);
}

void CPU::div() {
  int temp1 = pop();
  int temp2 = pop();
  int ans = temp1 / temp2;
  push(ans);
}

void CPU::savepc() {
  push(code_pointer);
}

void CPU::jmp() {
  int top_stack = pop();
  code_pointer = top_stack;
}

void CPU::cjmp() {
  int addr = pop();
  int cond = pop();

  if (cond) {
    code_pointer = addr;
  } else {
    code_pointer++;
  }
}

void CPU::inv() {
  int temp = pop();
  int invTemp = -temp;
  push(invTemp);
}

void CPU::mul() {
  int temp1 = pop();
  int temp2 = pop();
  int ans = temp1 * temp2;
  push(ans);
}

void CPU::grd() {
  int temp1 = pop();
  int temp2 = pop();
  push(temp1 > temp2);
}

void CPU::dup() {
  int top = pop();
  push(top);
  push(top);
}

void CPU::over() {
  int temp1 = pop();
  int temp2 = pop();
  push(temp2);
  push(temp1);
  push(temp2);
}

void CPU::halt() {
  code_pointer = -1;
  off = true;
}

void CPU::print() {
  int ans = pop();
  std::cout << "The answer is " << ans << "\n";
}

void CPU::runCpu() {
  if (code_pointer < CODE_SEGMENT_MAX && stack_pointer < STACK_SEGMENT_MAX) {

    if (!mux2cpu->check_empty()) {
      auto from_fifo = mux2cpu->pop_all();;
      int Data = from_fifo[DATA];

      /// check which instruction is
      if (prev_push) {
        push(Data);
        code_pointer++;
        prev_push = false;
        return;
      }

      switch (Data) {
      case PUSH:prev_push = true;
        code_pointer++;
        startCPU(code_pointer);
        break;
      case ADD:add();
        code_pointer++;
        break;
      case DIV:div();
        code_pointer++;
        break;
      case MUL:mul();
        code_pointer++;
        break;
      case INV:inv();
        code_pointer++;
        break;
      case LOAD:load();
        code_pointer++;
        break;
      case STORE:store();
        code_pointer++;
        break;
      case SAVEPC:savepc();
        code_pointer++;
        break;
      case JMP:jmp();
        code_pointer++;
        break;
      case CJMP:cjmp();
        break;
      case GREAT:grd();
        code_pointer++;
        break;
      case DUP:dup();
        code_pointer++;
        break;
      case OVER:over();
        code_pointer++;
        break;
      case SWAP:swap();
        code_pointer++;
        break;
      case HALT:halt();
        break;
      case PRINT:print();
        code_pointer++;
        break;
      }
    } else {
      startCPU(code_pointer);
    }

  }
}

#endif // CPU_H