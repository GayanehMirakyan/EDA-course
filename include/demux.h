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

  if (arb2demux->check_empty())
    return;

  data_width Data_demux = arb2demux->pop();
  data_width Address_demux = arb2demux->pop();
  data_width Mode_demux = arb2demux->pop();

  switch (Data_demux) {
  case 0: {
    if (ram2demux->check_empty())
      return;

    data_width Data_demux0 = ram2demux->pop();
    data_width Address_demux0 = ram2demux->pop();
    data_width Mode_demux0 = ram2demux->pop();

    demux2mux0->push(Data_demux0);
    demux2mux0->push(Address_demux0);
    demux2mux0->push(Mode_demux0);
    break;
  }
  case 1: {
    if (ram2demux->check_empty())
      return;

    data_width Data_demux1 = ram2demux->pop();
    data_width Address_demux1 = ram2demux->pop();
    data_width Mode_demux1 = ram2demux->pop();

    demux2mux1->push(Data_demux1);
    demux2mux1->push(Address_demux1);
    demux2mux1->push(Mode_demux1);
    break;
  }

  default:std::cout << "wrong select value\n";
  }
}
