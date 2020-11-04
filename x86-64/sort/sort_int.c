#include <stdio.h>
#include <ctype.h>

int array1[] = {3, 5, 20, 13, 7};

#define	ARRAY_SIZE(a) (sizeof a / sizeof a[0])

void print(int array[], int dim) {
	for (int i = 0; i < dim; i++)
		printf("%d ", array[i]);
	putchar('\n');
}

#if 1
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
#endif

void swap(int *a, int *b);

#if 0

void sort(int array[], int dim) {
	for (int i = 0; i < dim - 1; ++i)
		for (int j = 0; j < dim - 1 - i; ++j)
			if (array[j] > array[j + 1])
				swap(&array[j], &array[j + 1]);
}

#endif
void sort(int array[], int dim);

int main() {
	print(array1, ARRAY_SIZE(array1));
	sort(array1, ARRAY_SIZE(array1));
	print(array1, ARRAY_SIZE(array1));
}
