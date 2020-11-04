#include <stddef.h>

size_t my_strlen(const char *str) {
	size_t i;
	for (i = 0; str[i]; ++i)
	    ;
	return i;
}
