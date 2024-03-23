#ifndef MUX_H
#define MUX_H

#include <array>
#include <iostream>
#include "Fifo.h"
template<class data_width>
class MUX {
public:
  MUX(Fifo<8, data_width> *mux2cpu,
      Fifo<8, data_width> *demux02mux,
      Fifo<8, data_width> *demux12mux,
      Fifo<8, data_width> *dis2mux)
      : mux2cpu(mux2cpu), demux02mux(demux02mux), demux12mux(demux12mux), dis2mux(dis2mux) {}

  Fifo<8, data_width> *mux2cpu;
  Fifo<8, data_width> *demux02mux;
  Fifo<8, data_width> *demux12mux;
  Fifo<8, data_width> *dis2mux;

  void runMux();

};

/// mux02cpu0, demux02mux0, demux12mux0, dis02mux0

template<class data_width>
void MUX<data_width>::runMux() {

  if (!dis2mux->check_empty()) {
    data_width Data = dis2mux->pop();
    data_width Address = dis2mux->pop();
    data_width Mode = dis2mux->pop();

    switch (Data) {
    case 0: {
      if (demux02mux->check_empty())
        return;
      data_width Data_mux0 = demux02mux->pop();
      data_width Address_mux0 = demux02mux->pop();
      data_width Mode_mux0 = demux02mux->pop();

      mux2cpu->push(Mode_mux0);
      mux2cpu->push(Address_mux0);
      mux2cpu->push(Data_mux0);
      break;
    }
    case 1: {
      if (demux12mux->check_empty())
        return;
      data_width Data_mux1 = demux12mux->pop();
      data_width Address_mux1 = demux12mux->pop();
      data_width Mode_mux1 = demux12mux->pop();

      mux2cpu->push(Mode_mux1);
      mux2cpu->push(Address_mux1);
      mux2cpu->push(Data_mux1);
      break;
    }
    default:std::cout << "wrong selected value\n";
    }

  }
}

#endif // MUX_H