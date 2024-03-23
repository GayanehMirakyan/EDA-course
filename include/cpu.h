#ifndef CPU_H
#define CPU_H
#include <array>
#include "Fifo.h"


class CPU {
public:

  CPU(Fifo<8, int> *cpu2dis,
      Fifo<8, int> *mux2cpu
  ) : cpu2dis(cpu2dis), mux2cpu(mux2cpu) {
    // TODO change
    cpu2dis->push(148);
    cpu2dis->push(1);
    cpu2dis->push(0); //???
  }

  void runCpu();

  Fifo<8, int> *cpu2dis;
  Fifo<8, int> *mux2cpu;

};

void CPU::runCpu() {

  if (!mux2cpu->check_empty()) {

    int Data = mux2cpu->pop();
    int Address = mux2cpu->pop();
    int Mode = mux2cpu->pop();

    if (Mode == WRITE) {
      /// send data to ram
      //
      std::cerr << "runCpu read \n" << Data << "\n";
    } else if (Mode == READ) {
      //
      std::cerr << "runCpu write \n";
    }

  }
}


#endif // CPU_H