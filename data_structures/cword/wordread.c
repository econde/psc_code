#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	WORD_CHUNK	30

static char *word_ptr;
static size_t word_max_size;

static void wordfree(void) {
	free (word_ptr);
}

static int is_separator(char *separators, char c) {
	return strchr(separators, c) != NULL;
}

char *wordread(FILE *file, char *separators) {
	int index = 0;
	if (word_ptr == NULL) {
		word_ptr = malloc(WORD_CHUNK);
		if (word_ptr == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		word_max_size = WORD_CHUNK;
		atexit(wordfree);
	}
	int c;
	do {
		c = fgetc(file);
		if (c == EOF)
			return NULL;
	} while (is_separator(separators, c));

	while ( !is_separator(separators, c) && c != EOF) {
		word_ptr[index++] = c;
		if (index == (word_max_size - 1)) { /* sempre uma posição disponível */
			char *aux = realloc(word_ptr, word_max_size + WORD_CHUNK);
			if (aux == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			word_max_size += WORD_CHUNK;
			word_ptr = aux;
		}
		c = fgetc(file);
	}
	if (index == 0 && c != '\n')
		return NULL;
	word_ptr[index] = '\0';
	return word_ptr;
}
