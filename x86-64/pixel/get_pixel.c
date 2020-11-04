#include <stdio.h>

typedef struct {
    int id;
    unsigned int dx;
    unsigned int dy;
    unsigned int *bitmap;
} Icon;

int get_pixel(Icon **icons, int id, unsigned int x, unsigned int y) {
    for (Icon *icon = *icons; icon != NULL; icon = *++icons)
		if (icon->id == id) {
			unsigned int idx = icon->dx * y + x;
			return (icon->bitmap[idx >> 5] >> (idx & 0x1f)) & 1;
		}
    return -1;
}
