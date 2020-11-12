#include <string.h>
#include <stdlib.h>

int get_year(const char *date) {
	size_t l = strlen(date) + 1;
	char buffer[l];
	strcpy(buffer, date);
	return atoi(strtok(buffer, "-/ "));
}
