#ifndef VECTOR_H
#define VECTOR_H

typedef struct PVector {
	void **buffer;
	size_t current_size, max_size, chunk;
} PVector;

PVector *pvector_create(int chunk);

void pvector_destroy(PVector *);

size_t pvector_sorted_search(PVector *vector, void *key,
							int (*cmp)(const void *, const void *), size_t *index);

size_t pvector_search(PVector *vector, void *key,
					int (*cmp)(const void *, const void *));

size_t pvector_size(PVector *vector);

int pvector_insert(PVector *vector, void *element, size_t index);

void pvector_remove(PVector *vector, size_t index);

void pvector_sort(PVector *vector, int (*cmp)( const void *, const void *));

int pvector_sort_insert(PVector *vector, void *element,
						int (*cmp)( const void *, const void *));

int pvector_sort_remove(PVector *vector, void *element,
					int (*cmp)(const void *, const void *));

void pvector_foreach(PVector *vector, void(*do_it)(void *));

void * pvector_at(PVector * vector, int index);
void * pvector_assign(PVector * vector, int index, void * element);

#endif
