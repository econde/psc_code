#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

char *wordread(FILE *file, char *separators);

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

#define	ARRAY_SIZE(a)	(sizeof a / sizeof a[0])

char separators[] = " \t\n.:,;*+/()[]{}!?\"\'=-";

typedef struct Word {
	char *text;
	int counter;
} Word;

struct Word words[30000];
int words_counter;

void words_insert(char *word) {
	for (int i = 0; i < words_counter; ++i)
		if (strcmp(words[i].text, word) == 0) {
			words[i].counter++;
			return;
		}
	if (words_counter < ARRAY_SIZE(words)) {
		words[words_counter].counter = 1;
		words[words_counter].text = malloc(strlen(word) + 1);
		if (words[words_counter].text == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		strcpy(words[words_counter].text, word);
		words_counter++;
	}
}

void swap(Word *a, Word *b) {
	Word aux = *a;
	*a = *b;
	*b = aux;
}

void words_sort(Word array[], size_t array_length) {
	for (size_t i = 0; i < array_length - 1; i++)
		for (size_t j = 0; j < array_length - 1 - i; j++)
			if (array[j].counter < array[j + 1].counter) {
				swap(&array[j], &array[j + 1]);
			}
}

void words_print(Word array[], size_t array_length) {
	printf("Número de palavras = %d\n", words_counter);
	for (size_t i = 0; i < array_length - 1; i++)
		printf("%s - %d\n", words[i].text, array[i].counter);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return 1;
	}

	FILE *fd = fopen(argv[1], "r");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s): %s\n", argv[1], strerror(errno));
		return 1;
	}

	unsigned initial = get_time();
	char *word;
	while ((word = wordread(fd, separators)) != NULL) {
		words_insert(word);
	}
	unsigned elapsed = get_time() - initial;
	words_sort(words, words_counter);
	words_print(words, 10);
	printf("Time: %d\n", elapsed);
	fclose(fd);
}
















