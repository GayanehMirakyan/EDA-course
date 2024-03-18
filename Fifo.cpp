#include "Fifo.h"

template<int depth, class data_width>
Fifo<depth, data_width>::Fifo() : write_ptr(0), read_ptr(0), full(false), empty(true), count(0) {}

//template<int depth, class data_width>
//void Fifo<depth, data_width>::step(bool reset, bool write, bool read, data_width data_in) {
//  if (reset) {
//    write_ptr = 0;
//    read_ptr = 0;
//    data_out = 0;
//    full = false;
//    empty = true;
//  } else {
//    empty = check_empty();
//    full = check_full();
//    if (write && !full) {
//      push(data_in);
//    } else if (read && !empty) {
//      pop();
//    }
//  }
//}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_empty() {
  return count == 0;
}

template<int depth, class data_width>
bool Fifo<depth, data_width>::check_full() {
  return count == 7;
}

template<int depth, class data_width>
data_width Fifo<depth, data_width>::get_data_out() const {
  return data_out;
}

template<int depth, class data_width>
void Fifo<depth, data_width>::push(std::array<data_width, 3> data) {
  // FIXME: make push with mode, data and address
  if (count >= 8) {
    std::cout << "---Cannot push: Buffer Full---" << std::endl;
  } else {
    fifo[count][DATA] = data[DATA];
    fifo[count][MODE] = data[MODE];
    fifo[count][ADDRESS] = data[ADDRESS];

    count++;
    std::cout << "Pushed " << data[DATA] << std::endl;
  }
}

template<int depth, class data_width>
std::array<data_width, 3> Fifo<depth, data_width>::pop() {
  std::array<int, 3> defArr = {-1, -1, -1};
  if (fifo.empty()) {
    std::cout << "---Cannot Pop: Buffer Empty---" << std::endl;
    return defArr;
  }
  /// [mode, address, data]
  data_width data = fifo[count - 1][DATA];
  count--;
  std::cout << "-------------------------------Poped " << data << std::endl;
  return fifo[count];
}

template
class Fifo<8, int>;