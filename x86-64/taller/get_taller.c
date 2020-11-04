typedef struct person {
    char name[20];
    int age;
    int weight;
    int height;
} Person;

Person *get_taller(Person *people, size_t n_people) {
	size_t taller = 0;
	for (size_t i = 1; i < n_people; ++i)
		if (people[i].height > people[taller].height)
			taller = i;
	return &people[taller];
}
