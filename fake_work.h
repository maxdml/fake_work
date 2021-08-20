#ifndef fake_h__
#define fake_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
static inline uint64_t fw_rdtsc(void) {
    uint32_t a, d;
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static inline uint64_t fw_rdtscp(uint32_t *auxp) {
    uint32_t a, d, c;
    asm volatile("rdtscp" : "=a" (a), "=d" (d), "=c" (c));
    if (auxp)
        *auxp = c;
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

inline static void fake_work(unsigned int nloops) {
    for (unsigned int i = 0; i++ < nloops;) {
        asm volatile("nop");
    }
}
inline static void fake_work2(unsigned int run_ns, double freq) {
    uint64_t stop = fw_rdtsc() + freq * run_ns;
    while (fw_rdtsc() < stop)
        asm volatile("pause");
}



#ifdef __cplusplus
}
#endif

#endif  // fake_h__
