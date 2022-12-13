#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
	void *buffer;
	size_t element_size, current_size, max_size, chunk_size;
} Vector;

Vector *vector_create(size_t element_size, size_t chunk_size);

void vector_destroy(Vector *);

size_t vector_sorted_search(Vector *vector, void *key,
							int (*cmp)(const void *, const void *), size_t *index);

size_t vector_search(Vector *vector, void *key,
					int (*cmp)(const void *, const void *));

size_t vector_size(Vector *vector);

int vector_insert(Vector *vector, void *element, size_t index);

void vector_remove(Vector *vector, size_t index);

void vector_sort(Vector *vector, int (*cmp)( const void *, const void *));

int vector_sort_insert(Vector *vector, void *element,
						int (*cmp)( const void *, const void *));

int vector_sort_remove(Vector *vector, void *element,
					int (*cmp)(const void *, const void *));

void vector_foreach(Vector *vector, void(*do_it)(void *));

void *vector_at(Vector * vector, int index);

void *vector_assign(Vector * vector, int index, void * element);

#endif
