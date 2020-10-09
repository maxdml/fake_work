#include <iostream>
#include "fake_work.h"

static inline uint64_t rdtsc(void) {
    uint32_t a, d;
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static inline uint64_t rdtscp(uint32_t *auxp) {
    uint32_t a, d, c;
    asm volatile("rdtscp" : "=a" (a), "=d" (d), "=c" (c));
    if (auxp)
        *auxp = c;
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

int main (int argc, char *argv[]) {
    double freq = 2.5;
	uint64_t start, end;

	unsigned int run_ns = atol(argv[1]);
    unsigned int nloops = run_ns * 2.5;
    std::cout << "=====================================" << std::endl;
    std::cout << "Running for " << nloops << " iterations " << std::endl;
	start = rdtscp(NULL);
    fake_work(nloops);
	end = rdtscp(NULL);
    std::cout << "Ran for " << end - start << " cycles --- " << (end - start) / freq << " ns";
    std::cout << "=====================================" << std::endl;

    // This loop calibrates #iterations per nanosec
	start = rdtsc();
    for (int i = 0; i < 100000000; ++i) {
        asm volatile("nop");
    }
    end = rdtscp(NULL);
    double nanos = (end - start) / freq;
    double ter_per_ns = 100000000 / nanos;

    std::cout << "nanos: " << nanos << std::endl;
    std::cout << "ter per ns: " << ter_per_ns << std::endl;

    return 0;
}
