#ifndef ARBITER_H
#define ARBITER_H
#include <array>
#include "Fifo.h"

template<class data_width>
void runArbiter(Fifo<8, data_width> fifo);

#endif  // ARBITER_H