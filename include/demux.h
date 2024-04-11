#include <array>
#include <iostream>

template<class data_width>

class DEMUX {
public:
  DEMUX(Fifo<8, data_width> *ram2demux,
        Fifo<8, data_width> *arb2demux,
        Fifo<8, data_width> *demux2mux0,
        Fifo<8, data_width> *demux2mux1)
      : ram2demux(ram2demux), arb2demux(arb2demux), demux2mux0(demux2mux0), demux2mux1(demux2mux1) {}

  Fifo<8, data_width> *ram2demux;
  Fifo<8, data_width> *arb2demux;
  Fifo<8, data_width> *demux2mux0;
  Fifo<8, data_width> *demux2mux1;

  void runDemux();

};

template<class data_width>
void DEMUX<data_width>::runDemux() {

  if (!arb2demux->check_empty() && !ram2demux->check_empty()) {

    /// select
    auto from_fifo = arb2demux->pop_all();;
    data_width Data_demux = from_fifo[DATA];

    switch (Data_demux) {
    case 0: {
      if (ram2demux->check_empty())
        return;

      auto from_fifo_0 = ram2demux->pop_all();;
      data_width Mode_demux0 = from_fifo_0[MODE];
      data_width Address_demux0 = from_fifo_0[ADDRESS];
      data_width Data_demux0 = from_fifo_0[DATA];

      demux2mux0->push_all(Mode_demux0, Address_demux0, Data_demux0);

      break;
    }
    case 1: {
      if (ram2demux->check_empty())
        return;

      auto from_fifo_1 = ram2demux->pop_all();;
      data_width Mode_demux1 = from_fifo_1[MODE];
      data_width Address_demux1 = from_fifo_1[ADDRESS];
      data_width Data_demux1 = from_fifo_1[DATA];

      demux2mux1->push_all(Mode_demux1, Address_demux1, Data_demux1);

      break;
    }

    default:std::cout << "wrong select value\n";
    }

  }
}
