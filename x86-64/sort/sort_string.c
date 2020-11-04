#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define	ARRAY_SIZE(a) (sizeof a / sizeof a[0])

char *names[] = {"Ana", "Luis", "Manuel", "Joaquim"};

void swap(char **a, char **b) {
	char *tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(char *array[], size_t size) {
	for (size_t i = 0; i < size - 1; i++)
		for (size_t j = 0; j < size - i - 1; j++)
			if (strcmp(array[j], array[j + 1]) > 0)
				swap(&array[j], &array[j + 1]);
}

void print(char *array[], size_t size) {
	for (size_t i = 0; i < size; i++)
		printf("%s\n", array[i]);
}

int main() {
	print(names, ARRAY_SIZE(names));
	sort(names, ARRAY_SIZE(names));
	print(names, ARRAY_SIZE(names));
}
