#include <stdio.h>

typedef struct {
    int id;
    unsigned int dx;
    unsigned int dy;
    unsigned int *bitmap;
} Icon;

int get_pixel(Icon **icons, int id, unsigned int x, unsigned int y);

unsigned image1[] = {0xff, 0xff};

unsigned image2[] = {0xff, 0xff};

Icon icon1 = {33, 64, 64, image1};
Icon icon2 = {44, 64, 64, image2};

Icon *icons[] = {&icon1, &icon2};

int main() {
	get_pixel(icons, 33, 20, 20);
}

