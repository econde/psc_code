#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector *vector_create(int chunk) {
	Vector *vector = malloc(sizeof *vector);
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

int vector_sorted_insert(Vector *vector, void *element,
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
size_t vector_search(Vector *vector, void *key,
					int (*cmp)(const void *, const void *)) {
	for (size_t i = 0; i < vector->current_size; ++i)
		if (cmp(vector->buffer + i, key))
			return i;
	return 0;
}

size_t vector_size(Vector * vector) {
	return vector->current_size;
}

void *vector_at(Vector * vector, int index) {
	return vector->buffer[index];
}

void *vector_assign(Vector * vector, int index, void * element) {
	if (vector->current_size <= index)
		vector->current_size = index + 1;
	/* falta verificar se é necessário alocar mais memória */
	return vector->buffer[index] = element;
}

int vector_insert(Vector *vector, void *element, size_t index) {
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

void vector_remove(Vector *vector, size_t index) {
	memmove(&vector->buffer[index], &vector->buffer[index + 1],
		(vector->current_size - index - 1) * sizeof *vector->buffer);
	vector->current_size--;
}

void vector_sort(Vector *vector, int (*cmp)( const void *, const void *)) {
	qsort(vector->buffer, vector->current_size, sizeof *vector->buffer, cmp);
}

int vector_sort_remove(Vector * vector, void *element,
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

void vector_foreach(Vector * vector, void(*do_it)(void *)) {
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
	
	Vector * v = vector_create(2);
	vector_insert(v, &a, compare_int);
	vector_insert(v, &b, compare_int);
	vector_insert(v, &c, compare_int);
	vector_for_each(v, print_int);
}
 
#endif
