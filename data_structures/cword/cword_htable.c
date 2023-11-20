#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

char *wordread(FILE *file, char *separators);

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

typedef struct Word {
	char *text;
	int counter;
} Word;

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

static inline int min(int a, int b) {
	return a < b ? a : b;
}

#include "htable.h"

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

void free_words(void *data, void *context) {
	free(((Word *)data)->text);
	free(data);
}

//------------------------------------------------------------------------------

#include "slist.h"

int cmp_counter(const void *data, const void *context) {
	Word *ref = (Word *)data;
	Word *new = (Word *)context;
	if (ref->counter > new->counter)
		return -1;
	else if (ref->counter < new->counter)
		return 1;
	return 0;
}

void insert_in_list(void *data, void *context) {
	SList_node *list = *(SList_node **)context;
	list = slist_insert_sort(list, cmp_counter, data);
	*(SList_node **)context = list;
}

SList_node *htable_to_sortedlist(Htable *htable) {
	SList_node *list = NULL;
	htable_foreach(htable, insert_in_list, &list);
	return list;
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
	char *word_text;
	while((word_text = wordread(fd, separators)) != NULL) {
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
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %ld Time = %ld\n",
			nwords, htable_size(htable), duration);
	printf("Collisions = %d\n", htable_collisions(htable));

	SList_node *list = htable_to_sortedlist(htable);

	int i = 0;
	for (SList_node *p = list; p != NULL && i < 10; p = p->next, i++) {
		Word *word = (Word *)p->data;
		printf("%s - %d\n", word->text, word->counter);
	}
	slist_destroy(list);

	fclose(fd);
	htable_foreach(htable, free_words, NULL);
	htable_destroy(htable);
}

#if 0
void (void *data) {
	Word *word = (Word *)data;
}

Vector *htable_to_vector(Htable *htable) {
	Vector *vector = vector_create();
	htable_foreach(htable,
}
#endif


