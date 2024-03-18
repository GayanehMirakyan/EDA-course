#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <array>
#include "Fifo.h"
#include "mux.h"
#include "arbiter.h"
template<class data_width>
void runDispatcher(Fifo<8, data_width> fifo);

#endif // DISPATCHER_H