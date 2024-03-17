#include <array>
#include <iostream>

template<class data_width>
class Demux {
public:
    Demux();

    void demux(const data_width &in,
               data_width &a,
               data_width &b,
               data_width &c,
               data_width &d,
               int select);

};
