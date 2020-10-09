#include "fake_work.h"
#ifdef __cplusplus
extern "C" {
#endif
void fake_work(unsigned int nloops) {
    for (unsigned int i = 0; i++ < nloops;) {
        asm volatile("nop");
    }
}
#ifdef __cplusplus
}
#endif
