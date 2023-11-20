#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector_ptr.h"

PVector *pvector_create(int chunk) {
	PVector *vector = malloc(sizeof *vector);
	if (NULL == vector)
		return NULL;
	vector->buffer = malloc(chunk * sizeof *vector->buffer);
	if (NULL == vector->buffer) {
		free(vector);
		return NULL;
	}
	vector->chunk = chunk;
	vector->max_size = chunk;
	vector->current_size = 0;
	return vector;
}

void pvector_destroy(PVector *vector) {
	free(vector->buffer);
	free(vector);
}

/*	pesquisa binária sobre vetor ordenado
 *	retorna um valor booleano indicando se encontrou
 *	devolve através de index a posição onde encontrou ou deveria encontrar
 */
size_t pvector_sorted_search(PVector *vector, void *key,
							int (*cmp)(const void *, const void *), size_t *index) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	void **buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp(&buffer[middle], key);
		if (cmp_result < 0)
			ref = left = middle + 1;
		else if (cmp_result > 0)
			ref = right = middle;
		else {
			*index = middle;
			return 1;
		}
		middle = left + (right - left) / 2;
	}
	*index = ref;
	return 0;
}

int pvector_sorted_insert(PVector *vector, void *element,
					int (*cmp)( const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	void **buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp(&buffer[middle], element);
		if (cmp_result > 0)
			ref = left = middle + 1;
		else if (cmp_result < 0)
			ref = right = middle;
		else
			return 1;
		middle = left + (right - left) / 2;
	}
	if (vector->current_size == vector->max_size) {
		vector->buffer = buffer = realloc(buffer,
				(vector->current_size + vector->chunk) * sizeof *vector->buffer);
		if (buffer == NULL)
			return 0;
		vector->max_size += vector->chunk;
	}
	memmove(&buffer[ref + 1], &buffer[ref], (vector->current_size - ref) * sizeof *buffer);
	buffer[ref] = element;
	vector->current_size++;
	return 1;
}

/*	pesquisa sequencial
 *	retorna a posição onde encontrou ou a dimensão caso não tenha encontrado.
 */
size_t pvector_search(PVector *vector, void *key,
					int (*cmp)(const void *, const void *)) {
	for (size_t i = 0; i < vector->current_size; ++i)
		if (cmp(vector->buffer + i, key))
			return i;
	return 0;
}

size_t pvector_size(PVector * vector) {
	return vector->current_size;
}

void *pvector_at(PVector * vector, int index) {
	return vector->buffer[index];
}

void *pvector_assign(PVector * vector, int index, void * element) {
	if (vector->current_size <= index)
		vector->current_size = index + 1;
	/* falta verificar se é necessário alocar mais memória */
	return vector->buffer[index] = element;
}

int pvector_insert(PVector *vector, void *element, size_t index) {
	void **buffer = vector->buffer;
	if (index >= vector->current_size) {
		if (index >= vector->max_size) {
			vector->max_size = (index / vector->chunk + 1) * vector->chunk;
			vector->buffer = buffer = realloc(buffer, vector->max_size * sizeof *buffer);
			if (NULL == buffer)
				return 0;
		}
		buffer[index] = element;
		vector->current_size = index + 1;
		return 1;
	}	/* index < vector->current_size */
	if (vector->current_size == vector->max_size) {
		vector->max_size += vector->chunk;
		vector->buffer = buffer = realloc(buffer, vector->max_size * sizeof *buffer);
		if (NULL == buffer)
			return 0;
	}
	memmove(&buffer[index + 1], &buffer[index], (vector->current_size - index) * sizeof *buffer);
	buffer[index] = element;
	vector->current_size++;
	return 1;
}

void pvector_remove(PVector *vector, size_t index) {
	memmove(&vector->buffer[index], &vector->buffer[index + 1],
		(vector->current_size - index - 1) * sizeof *vector->buffer);
	vector->current_size--;
}

void pvector_sort(PVector *vector, int (*cmp)( const void *, const void *)) {
	qsort(vector->buffer, vector->current_size, sizeof *vector->buffer, cmp);
}

int pvector_sort_remove(PVector * vector, void *element,
					int (*cmp)(const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	void **buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp(&buffer[middle], element);
		if (cmp_result > 0)
			left = middle + 1;
		else if (cmp_result < 0)
			right = middle;
		else {
			memmove(&buffer[middle], &buffer[middle + 1],
				(vector->current_size - middle - 1) * sizeof *buffer);
			vector->current_size--;
			return 1;
		}
		middle = left + (right - left) / 2;
	}
	return 0;
}

void pvector_foreach(PVector * vector, void(*do_it)(void *)) {
	for (size_t i = 0; i < vector->current_size; ++i)
		do_it(vector->buffer[i]);
}

#if 0

void print_int(void * data) {
	printf("%4d\n", *(int*) data);
}

int * new_int(int value) {
	int * new = malloc(sizeof *new);
	assert(new != NULL);
	*new = value;
	return new;
}

int compare_int(const void * a, const void * b) {
	return *(int *) a - *(int *) b;
}

int main() {
	int a = 3, b = 5, c = 4;

	PVector * v = pvector_create(2);
	pvector_insert(v, &a, compare_int);
	pvector_insert(v, &b, compare_int);
	pvector_insert(v, &c, compare_int);
	pvector_for_each(v, print_int);
}

#endif
