#include <stdint.h>
#include "framebuffer.h"

#define GPIO_BASE 0x3F200000
#define GPFSEL1 (GPIO_BASE + 0x04)
#define GPSET0 (GPIO_BASE + 0x1C)
#define GPCLR0 (GPIO_BASE + 0x28)

volatile uint32_t *gpio;

void gpio_init() {
    gpio = (uint32_t *) GPFSEL1;
    *gpio &= ~(0x7 << 24);
    *gpio |= (0x1 << 24);
}

void gpio_set() {
    gpio = (uint32_t *) GPSET0;
    *gpio |= (0x1 << 18);
}

void gpio_clear() {
    gpio = (uint32_t *) GPCLR0;
    *gpio |= (0x1 << 18);
}

void delay(int32_t count) {
    while (count--) {
        asm volatile("nop");
    }
}

void kernel_main(void) {
    framebuffer_init(1920, 1080); // Initialize framebuffer with desired resolution
    framebuffer_set_color(0xFF0000FF); // Set the screen color (RGBA8 format)

    gpio_init();

    while (1) {
        gpio_set();
        delay(1000000);
        gpio_clear();
        delay(1000000);
    }
}