#ifndef MUX_H
#define MUX_H

#include <array>
#include <iostream>
#include "Fifo.h"

namespace mux{
template<class data_width>
void mux(Fifo<8, data_width> &fifo_a,
         Fifo<8, data_width> &fifo_b,
         Fifo<8, data_width> &fifo_c,
         Fifo<8, data_width> &fifo_out,
         int select);

template<class data_width>
void runMux(Fifo<8, int> &fifo_select,
            Fifo<8, data_width> &fifo_a = nullptr,
            Fifo<8, data_width> &fifo_b = nullptr,
            Fifo<8, data_width> &fifo_c = nullptr,
            Fifo<8, data_width> &fifo_out = nullptr);

} //mux

#endif // MUX_H