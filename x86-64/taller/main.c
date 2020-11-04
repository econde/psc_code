#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct person {
    char name[20];
    int age;
    int weight;
    int height;
} Person;

Person *get_taller(Person *people, size_t n_people);

Person people[] = {
	{"Ana", 30, 70, 177},
	{"Manuel", 30, 70, 187}
};

int main() {
    char *taller_name = get_taller(people, ARRAY_SIZE(people))->name;
}
