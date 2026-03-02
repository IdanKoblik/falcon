#ifndef VGA_H
#define VGA_H

#include <stdint.h>

typedef struct vga_info_t {
    uint8_t width;
    uint8_t height;
    uint16_t *buffer;

    uint32_t x;
    uint32_t y;
} vga_info_t;

extern vga_info_t vga_info;

void vga_put_char(char c, uint8_t color, int x, int y);
void vga_color_print(const char *str, uint8_t color);
void vga_print(const char *str);
void vga_clear(void);
void vga_init(void);

#endif // VGA_H
