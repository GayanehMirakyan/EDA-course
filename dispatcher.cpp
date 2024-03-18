#include "dispatcher.h"
#include "Fifo.h"
#include "mux.h"

template<class data_width>
void runDispatcher(std::array<data_width, 3> fifoElem) {
  if(fifoElem[MODE] == WRITE) {

  } else if(fifoElem[MODE] == READ) {

  }
}