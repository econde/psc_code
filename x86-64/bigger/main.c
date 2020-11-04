#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int find_bigger(int array[], size_t array_size);

int a[] = { 10, 40, 30, 5};

int main() {
	int b = find_bigger(a, ARRAY_SIZE(a));
}
