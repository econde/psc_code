#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

char *wordread(FILE *file, char *separators);

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

typedef struct Word {
	char *text;
	int counter;
} Word;

/*------------------------------------------------------------------------------
 * Word
 */
char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

static inline int min(int a, int b) {
	return a < b ? a : b;
}

#include "tree.h"

Tree_node *words;

int word_cmp_text(const void *a, const void *b) {
	return strcmp(((Word *)a)->text, ((Word*)b)->text);
}

void free_words(void *data) {
	free(((Word *)data)->text);
	free(data);
}

int main(int argc, char *argv[]) {
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	int nwords = 0;
	words = NULL;
	long initial = get_time();
	char *word_text;
	while((word_text = wordread(fd, separators)) != NULL) {
		nwords++;
		Word key = {.text = word_text};
		Tree_node *node = tree_search(words, &key, word_cmp_text);
		if (node != NULL) {
			Word *word = tree_data(node);
			word->counter++;
		}
		else {
			Word *word = malloc(sizeof(Word));
			if (word == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			word->counter = 1;
			word->text = strdup(word_text);
			if (word->text == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			words = tree_insert(words, word, word_cmp_text);
		}
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %ld Time = %ld\n",
		nwords, tree_size(words), duration);
	printf("Profundidade da árvore = %d\n", tree_depth(words));
	/* libertar a memória alocada */
	fclose(fd);
	tree_foreach(words, free_words);
	tree_destroy(words);
}
