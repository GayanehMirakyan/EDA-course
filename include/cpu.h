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
  ) : cpu2dis(cpu2dis), mux2cpu(mux2cpu), prev_push(false) {
    // TODO change
  }

  int code_pointer = CODE_SEGMENT_MIN;
  int stack_pointer = STACK_SEGMENT_MIN;
  int data_pointer = DATA_SEGMENT_MIN;
  bool prev_push;

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
  std::cout << "is PUSH inst\n";
  cpu2dis->push_all(WRITE, stack_pointer, Data);
//  bus.runSendToRam();
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
  bus.runSendToCpu();
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

void CPU::store() {
  /// idk
  int temp = pop();
  push(temp);
  cpu2dis->push_all(WRITE, data_pointer, temp);
  data_pointer++;
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
  int ans = temp2 / temp1;
  push(ans);
}

void CPU::savepc() {
  ///??????????
}

void CPU::jmp() {
  int top_stack = pop();
  /// program counter
  code_pointer = top_stack;
}

void CPU::cjmp() {
  int cond = pop();
  int addr = pop();
  if (cond) {
    code_pointer = addr;
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
//????????????????????
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
//??????????????????/
}

void CPU::print() {
  ram.print_memory();
}

void CPU::runCpu() {
  if (code_pointer < CODE_SEGMENT_MAX && stack_pointer < STACK_SEGMENT_MAX) {

    if (!mux2cpu->check_empty()) {
      std::cout << "in CPU: mux to cpu fifo is not empty\n";
      int Data = mux2cpu->pop();
      int Address = mux2cpu->pop();
      int Mode = mux2cpu->pop();
      /// check which instruction is
      if (prev_push) {
        std::cout << "prev_push is true\n";
        push(Data);
        code_pointer++;
        prev_push = false;
        return;
      }

      switch (Data) {
      case PUSH:std::cout << "push\n";
        prev_push = true;
        code_pointer = Address;
        code_pointer++;
        startCPU(code_pointer);
        break;
      case ADD:std::cout << "add\n";
        code_pointer++;
        add();
        break;
      case DIV:code_pointer++;
        div();
        break;
      case MUL:code_pointer++;
        mul();
        break;
      case INV:std::cout << "INV instruction\n";
        code_pointer++;
        inv();
        break;
      case LOAD:code_pointer++;
        load();
        break;
      case STORE:code_pointer++;
        store();
        break;
      case SAVEPC:code_pointer++;
        savepc();
        break;
      case JMP:code_pointer++;
        jmp();
        break;
      case CJMP:code_pointer++;
        cjmp();
        break;
      case GREAT:code_pointer++;
        grd();
        break;
      case DUP:code_pointer++;
        dup();
        break;
      case OVER:code_pointer++;
        over();
        break;
      case SWAP:code_pointer++;
        swap();
        break;
      case HALT:code_pointer++;
        halt();
        break;
      case PRINT:code_pointer++;
        print();
        break;
      }
    } else {
      startCPU(code_pointer);
    }

  }
}

#endif // CPU_H