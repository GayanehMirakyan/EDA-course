#include "Fifo.h"
#include "mux.h"

void fifo_test() {
    Fifo<8, int> fifo;

    for (int i = 0; i < 15; i++) {
        fifo.step(false, true, false, 1); // Write 1
        fifo.step(false, true, false, 2); // Write 2
        fifo.step(false, false, true); // Read
        // fifo.step(false, true, false, i); // Write i
        // fifo.step(false, true, false, i); // Write i
    }
    fifo.step(true, false, false); // Reset


    // std::cout << "Is empty: " << fifo.check_empty() << std::endl;
    // std::cout << "Is full: " << fifo.check_full() << std::endl;
    // std::cout << "Data out: " << fifo.get_data_out() << std::endl;
}

void mux_test() {


    Mux<int> mux;
//  if (fifo_a.)
    mux.mux(fifo_a, fifo_b, fifo_c, fifo_d);
}
//const data_width &a,
//const data_width &b,
//const data_width &c,
//const data_width &d,
//    data_width &out,
//int select


int main() {
    fifo_test();

    return 0;
}
