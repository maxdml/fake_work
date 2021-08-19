#include <iostream>
#include "fake_work.h"

int main (int argc, char *argv[]) {
    double freq = 2.59;
	uint64_t start, end;

	unsigned int run_ns = atol(argv[1]);
    unsigned int nloops = run_ns * freq;
    std::cout << "=====================================" << std::endl;
    std::cout << "Running for " << nloops << " iterations " << std::endl;
	start = fw_rdtscp(NULL);
    fake_work(nloops);
	end = fw_rdtscp(NULL);
    std::cout << "Ran for " << end - start << " cycles --- " << (end - start) / freq << " ns";
    std::cout << std::endl;
    std::cout << "=====================================" << std::endl;

    // Zygos spin technique
    std::cout << "=====================================" << std::endl;
    std::cout << "ZygOS spin technique" << std::endl;
    start = fw_rdtscp(NULL);
    fake_work2(run_ns, freq);
    end = fw_rdtscp(NULL);
    std::cout << "Ran for " << end - start << " cycles --- " << (end - start) / freq << " ns";
    std::cout << std::endl;
    std::cout << "=====================================" << std::endl;

    // This loop calibrates #iterations per nanosec
	start = fw_rdtsc();
    for (int i = 0; i < 100000000; ++i) {
        asm volatile("nop");
    }
    end = fw_rdtscp(NULL);
    double nanos = (end - start) / freq;
    double ter_per_ns = 100000000 / nanos;

    std::cout << "nanos: " << nanos << std::endl;
    std::cout << "ter per ns: " << ter_per_ns << std::endl;

    return 0;
}
