#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
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

#include "htable.h"

#include "list.h"

Htable *htable;

int word_cmp_text(const void *data, const void *b) {
	return strcmp(((Word *)data)->text, (char*)b);
}

int hash_function(const void *data) {
	const char *word_text = data;
	int hash = 0;
	while (*word_text)
		hash += *word_text++;
	return hash;
}

void free_words(void *data) {
	free(((Word *)data)->text);
	free(data);
}

int main(int argc, char *argv[]){
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(-1);
	}
	int nwords = 0;
	htable = htable_create(10000, hash_function, word_cmp_text);
	long initial = get_time();
	char *word_text = word_read(fd);
	while(word_text != NULL) {
		nwords++;
		Word *word = htable_lookup(htable, word_text);
		if (word != NULL) {
			word->counter++;
		}
		else {
			word = malloc(sizeof(Word));
			word->counter = 1;
			word->text = strdup(word_text);
			htable_insert(htable, word_text, word);
		}
		word_text = word_read(fd);
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %ld Time = %ld\n",
			nwords, htable_size(htable), duration);
	printf("Collisions = %d\n", htable_collisions(htable));
	fclose(fd);
	htable_foreach(htable, free_words);
	htable_destroy(htable);
}

