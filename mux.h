#include <array>
#include <iostream>
#include "Fifo.h"

template<class data_width>
class Mux {
private:

public:
    Mux();

    void mux(Fifo<8, data_width> &fifo_a,
             Fifo<8, data_width> &fifo_b,
             Fifo<8, data_width> &fifo_c,
             Fifo<8, data_width> &fifo_out,
             int select);

};

template<class data_width>
void runMux(Fifo<8, data_width> &fifo_a,
            Fifo<8, data_width> &fifo_b,
            Fifo<8, data_width> &fifo_c,
            Fifo<8, data_width> &fifo_d,
            Fifo<8, data_width> &fifo_out);
