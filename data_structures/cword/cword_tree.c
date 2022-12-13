#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

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

char *word_read(FILE *fd){
	static char buffer[100];
	int i = 0, c;
	do {
		c = fgetc(fd);
		if(c == EOF){
			return NULL;
		}
	}
	while (strchr(separators, c) != NULL);
	do {
		buffer[i++] = c;
		c = fgetc(fd);
		if(c == EOF)
			break;
	} while (strchr(separators, c) == NULL);
	buffer[i] = '\0';
	return buffer;
}

static inline int min(int a, int b) {
	return a < b ? a : b;
}

#include "tree.h"

Tree_node *words;

int word_cmp_text(void *a, void *b) {
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
		exit(-1);
	}
	int nwords = 0;
	words = NULL;
	long initial = get_time();
	char *word_text = word_read(fd);
	while(word_text != NULL) {
		nwords++;
		Word key = {.text = word_text};
		Tree_node *node = tree_search(words, &key, word_cmp_text);
		if (node != NULL) {
			Word *word = tree_data(node);
			word->counter++;
		}
		else {
			Word *word = malloc(sizeof(Word));
			word->counter = 1;
			word->text = strdup(word_text);
			words = tree_insert(words, word, word_cmp_text);
		}
		word_text = word_read(fd);
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
