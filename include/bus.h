#ifndef BUS_H
#define BUS_H

class BUS {
private:
    Fifo<8, int> dis02arb0;
    Fifo<8, int> dis02arb1;
    Fifo<8, int> dis02mux0;
    Fifo<8, int> arb02demux0;
    Fifo<8, int> demux02mux0;
    Fifo<8, int> demux02mux1;
public:
    DISPATCHER<int> dis0;
    ARBITER<int> arb0;
    MUX<int> mux0;
    DEMUX<int> demux0;
    Fifo<8, int> *cpu2dis;
    Fifo<8, int> *mux2cpu;
    Fifo<8, int> *ram2demux;
    Fifo<8, int> *arb2ram;

    BUS(Fifo<8, int> *cpu2dis, Fifo<8, int> *mux2cpu, Fifo<8, int> *arb2ram, Fifo<8, int> *ram2demux) : cpu2dis(
            cpu2dis), mux2cpu(mux2cpu), arb2ram(arb2ram), ram2demux(ram2demux),
            dis0(cpu2dis, &dis02arb0, &dis02arb1, &dis02mux0),
            arb0(&dis02arb0, &dis12arb0, &arb02demux0, arb2ram),
            mux0(mux2cpu, &demux02mux0, &demux12mux0, &dis02mux0),
            demux0(ram2demux, &arb02demux0, &demux02mux0, &demux02mux1) {}

    void runSendToRam() {
        dis0.runDispatcher();
        arb0.runArbiter();
    }

    void runSendToCpu() {
        demux0.runDemux();
        mux0.runMux();
    }
};

BUS bus(&cpu02dis0, &mux02cpu0, &arb02ram0, &ram02demux0);

#endif // BUS_H
