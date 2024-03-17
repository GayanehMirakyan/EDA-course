#include "Fifo.h"

template<int depth, class data_width>
Fifo<depth, data_width>::Fifo() : write_ptr(0), read_ptr(0), full(false), empty(true), count(0) {
    fifo.fill(0);
}

template<int depth, class data_width>
void Fifo<depth, data_width>::step(bool reset, bool write, bool read, data_width data_in) {
    if (reset) {
        write_ptr = 0;
        read_ptr = 0;
        data_out = 0;
        full = false;
        empty = true;
    } else {
        empty = check_empty();
        full = check_full();
        if (write && !full) {
            push(data_in);
        } else if (read && !empty) {
            pop();
        }
    }
}

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
void Fifo<depth, data_width>::push(data_width data) {
    if (count >= 8) {
        std::cout << "---Cannot push: Buffer Full---" << std::endl;
    } else {
        fifo[count] = data;
        count++;
        std::cout << "Pushed " << data << std::endl;
    }
}

template<int depth, class data_width>
data_width Fifo<depth, data_width>::pop() {
    if (fifo.empty()) {
        std::cout << "---Cannot Pop: Buffer Empty---" << std::endl;
        return -1;
    } else {
        data_width data = fifo[count - 1];
        count--;
        std::cout << "-------------------------------Poped " << data << std::endl;
        return data;
    }
}

template
class Fifo<8, int>;