#ifndef FIFO_H
#define FIFO_H

#include <array>
#include <iostream>

template<int depth, class data_width>
class Fifo {
public:
    Fifo();

    void step(bool reset, bool write, bool read, data_width data_in = 0);

    bool check_empty();

    bool check_full();

    data_width get_data_out() const;

    void push(data_width data);

    data_width pop();

private:
    std::array <data_width, depth> fifo;
    int write_ptr;
    int read_ptr;
    bool full;
    bool empty;
    data_width data_out;
    int count;
};

#endif // FIFO_H
