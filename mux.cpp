#include "mux.h"

template<class data_width>
void mux::mux(Fifo<8, data_width> &fifo_a,
              Fifo<8, data_width> &fifo_b,
              Fifo<8, data_width> &fifo_c,
              Fifo<8, data_width> &fifo_out,
              int select) {
  switch (select) {
  case 0:fifo_out.push(fifo_a.pop());
  case 1:fifo_out.push(fifo_b.pop());
  case 2:fifo_out.push(fifo_c.pop());

  default:std::cout << "wrong select value\n";
  }
}

template<class data_width>
void mux::runMux(Fifo<8, int> &fifo_select, Fifo<8, data_width> &fifo_a,
                 Fifo<8, data_width> &fifo_b,
                 Fifo<8, data_width> &fifo_c,
                 Fifo<8, data_width> &fifo_out) {
  while (true) {
    if (!fifo_select.check_empty()) {
      int selectData = fifo_select.pop()[DATA];
      if (selectData == 0 && !fifo_a.check_empty()) {
        mux(fifo_a, fifo_b, fifo_c, fifo_out, selectData);
        break;
      } else if (selectData == 1 && !fifo_b.check_empty()) {
        mux(fifo_a, fifo_b, fifo_c, fifo_out, selectData);
        break;
      } else if (selectData == 2 && !fifo_c.check_empty()) {
        mux(fifo_a, fifo_b, fifo_c, fifo_out, selectData);
        break;
      }
    }
  }
}

template void mux::runMux<int>(Fifo<8, int> &, Fifo<8, int> &, Fifo<8, int> &, Fifo<8, int> &, Fifo<8, int> &);