#include <stdlib.h>

size_t my_strlen(const char *);

size_t i = 0;

char message[] = "abcdef";

int main() {
	i = my_strlen(message);
	return i;
}
