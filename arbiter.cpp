#include "arbiter.h"
#include "Fifo.h"

template<class data_width>
void runArbiter(std::array<data_width, 3> fifoElem) {
  whiel(true) {
    if(fifoElem[MODE] == WRITE) {
      /// send data to ram
    } else if(fifoElem[MODE] == READ) {

    }
  }
}