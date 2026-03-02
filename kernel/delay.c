#include "delay.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm__ __volatile__("nop");
    }
}
