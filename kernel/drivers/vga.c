#include "vga.h"

vga_info_t vga_info = {
    .width = 80,
    .height = 25,
    .buffer = (uint16_t*)0xB8000,

    .x = 0,
    .y = 0
};

void vga_put_char(char c, uint8_t color, int x, int y) {
    if (!vga_info.buffer)
        return;

    int index = y * vga_info.width + x;
    vga_info.buffer[index] = (color << 8) | c;
}

void vga_color_print(const char* str, uint8_t color) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            vga_info.x = 0;
            vga_info.y++;
            if (vga_info.y >= vga_info.height)
                vga_info.y = vga_info.height - 1;

            continue;
        }

        vga_put_char(str[i], color, vga_info.x, vga_info.y);
        vga_info.x++;
        if (vga_info.x >= vga_info.width) {
            vga_info.x = 0;
            vga_info.y++;

            if (vga_info.y >= vga_info.height)
                vga_info.y = vga_info.height - 1;
        }
    }
}

void vga_print(const char* str) {
    vga_color_print(str,0x0F);
}

void vga_clear(void) {
    for (int y = 0; y < vga_info.height; y++) {
        for (int x = 0; x < vga_info.width; x++) {
            vga_put_char(' ', 0x0F, x, y);
        }
    }

    vga_info.x = 0;
    vga_info.y = 0;
}

void vga_init(void) {
    if (!vga_info.buffer) {
        vga_info.width = 80;
        vga_info.height = 25;
        vga_info.buffer = (uint16_t*)0xB8000;

        vga_info.x = 0;
        vga_info.y = 0;
    }

    vga_clear();
}
