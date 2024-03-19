#include <array>
#include <iostream>

template<class data_width>
Demux<data_width>::Demux() = default;

template<class data_width>
void Demux<data_width>::demux(const data_width &in,
                              data_width &a,
                              data_width &b,
                              data_width &c,
                              data_width &d,
                              int select) {
  switch (select) {
  case 0:a = in;
  case 1:b = in;
  case 2:c = in;
  case 3:d = in;
  default:std::cout << "wrong select value\n";
  }
}
