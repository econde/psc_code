#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector *vector_create(size_t element_size, size_t chunk_size) {
	Vector *vector = malloc(sizeof *vector);
	if (NULL == vector)
		return NULL;
	vector->buffer = malloc(element_size * chunk_size);
	if (NULL == vector->buffer) {
		free(vector);
		return NULL;
	}
	vector->element_size = element_size;
	vector->chunk_size = chunk_size;
	vector->max_size = chunk_size;
	vector->current_size = 0;
	return vector;
}

void vector_destroy(Vector *vector) {
	free(vector->buffer);
	free(vector);
}

/*	pesquisa binária sobre vetor ordenado
 *	retorna um valor booleano indicando se encontrou
 *	devolve através de index a posição onde encontrou ou deveria encontrar
 */
size_t vector_sorted_search(Vector *vector, void *key,
							int (*cmp)(const void *, const void *), size_t *index) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	char *buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp(buffer + middle * vector->element_size, key);
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

int vector_sorted_insert(Vector *vector, void *element,
					int (*cmp)( const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	char *buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp(buffer + middle * vector->element_size, element);
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
				(vector->current_size + vector->chunk_size) * vector->element_size);
		if (buffer == NULL)
			return 0;
		vector->max_size += vector->chunk_size;
	}
	memmove(buffer + (ref + 1) * vector->element_size,
			buffer + ref * vector->element_size,
			(vector->current_size - ref) * vector->element_size);
	memcpy(buffer + ref * vector->element_size,
			element, vector->element_size);
	vector->current_size++;
	return 1;
}

/*	pesquisa sequencial
 *	retorna a posição onde encontrou ou a dimensão caso não tenha encontrado.
 */
size_t vector_search(Vector *vector, void *key,
					int (*cmp)(const void *, const void *)) {
	for (size_t i = 0; i < vector->current_size; ++i)
		if (cmp((char *)vector->buffer + i * vector->element_size, key))
			return i;
	return 0;
}

size_t vector_size(Vector *vector) {
	return vector->current_size;
}

void *vector_at(Vector *vector, int index) {
	return (char *)vector->buffer + index * vector->element_size;
}

void *vector_assign(Vector *vector, int index, void *element) {
	if (vector->current_size <= index)
		vector->current_size = index + 1;
	/* falta verificar se é necessário alocar mais memória */
	return memcpy((char *)vector->buffer + index * vector->element_size,
				element, vector->element_size);
}

int vector_insert(Vector *vector, void *element, size_t index) {
	char *buffer = vector->buffer;
	if (index >= vector->current_size) {
		if (index >= vector->max_size) {
			vector->max_size = (index / vector->chunk_size + 1) * vector->chunk_size;
			vector->buffer = buffer = realloc(buffer, vector->max_size * vector->element_size);
			if (NULL == buffer)
				return 0;
		}
		memcpy(buffer + index * vector->element_size, element, vector->element_size);
		vector->current_size = index + 1;
		return 1;
	}	/* index < vector->current_size */
	if (vector->current_size == vector->max_size) {
		vector->max_size += vector->chunk_size;
		vector->buffer = buffer = realloc(buffer, vector->max_size * vector->element_size);
		if (NULL == buffer)
			return 0;
	}
	memmove(buffer + (index + 1) * vector->element_size,
			buffer +  index * vector->element_size,
			(vector->current_size - index) * vector->element_size);
	memcpy(buffer + index * vector->element_size, element, vector->element_size);
	vector->current_size++;
	return 1;
}

void vector_remove(Vector *vector, size_t index) {
	memmove((char *)vector->buffer + index * vector->element_size,
		(char *)vector->buffer + (index + 1) * vector->element_size,
		(vector->current_size - index - 1) * vector->element_size);
	vector->current_size--;
}

void vector_sort(Vector *vector, int (*cmp)(const void *, const void *)) {
	qsort(vector->buffer, vector->current_size, vector->element_size, cmp);
}

int vector_sort_remove(Vector *vector, void *element,
					int (*cmp)(const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	void **buffer = vector->buffer;
	while (left < right) {
		int cmp_result = cmp((char *)buffer + middle * vector->element_size, element);
		if (cmp_result > 0)
			left = middle + 1;
		else if (cmp_result < 0)
			right = middle;
		else {
			memmove((char *)buffer + middle * vector->element_size,
				(char *)buffer + (middle + 1) * vector->element_size,
				(vector->current_size - middle - 1) * vector->element_size);
			vector->current_size--;
			return 1;
		}
		middle = left + (right - left) / 2;
	}
	return 0;
}

void vector_foreach(Vector *vector, void(*do_it)(void *)) {
	for (size_t i = 0; i < vector->current_size; ++i)
		do_it((char *)vector->buffer + i * vector->element_size);
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

	Vector * v = vector_create(2);
	vector_insert(v, &a, compare_int);
	vector_insert(v, &b, compare_int);
	vector_insert(v, &c, compare_int);
	vector_for_each(v, print_int);
}

#endif
