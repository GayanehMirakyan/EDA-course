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

  if (!dis2mux->check_empty() && (!demux02mux->check_empty() || !demux12mux->check_empty())) {
    std::cout << " MUX \n";
    auto from_fifo = dis2mux->pop_all();;
    data_width Mode = from_fifo[MODE];
    data_width Address = from_fifo[ADDRESS];
    data_width Data = from_fifo[DATA];

    std::cerr << "Mode = " << Mode << "   Address = " << Address << "   Data = " << Data << "\n";

    switch (Data) {
    case 0: {
      if (demux02mux->check_empty())
        return;

      auto from_fifo_1 = demux02mux->pop_all();
      data_width Mode_mux0 = from_fifo_1[MODE];
      data_width Address_mux0 = from_fifo_1[ADDRESS];
      data_width Data_mux0 = from_fifo_1[DATA];
      std::cerr << Mode_mux0 << " " << Address_mux0 << " "<< Data_mux0 << "\n";

      mux2cpu->push_all(Mode_mux0, Address_mux0, Data_mux0);

      break;
    }
    case 1: {
      if (demux12mux->check_empty())
        return;
      auto from_fifo_1 = demux12mux->pop_all();
      data_width Mode_mux1 = from_fifo_1[MODE];
      data_width Address_mux1 = from_fifo_1[ADDRESS];
      data_width Data_mux1 = from_fifo_1[DATA];

      std::cerr << Mode_mux1 << " " << Address_mux1 << " "<< Data_mux1 << "\n";
      mux2cpu->push_all(Mode_mux1, Address_mux1, Data_mux1);

      break;
    }
    default:std::cout << "wrong selected value\n";
    }

  }
}

#endif // MUX_H