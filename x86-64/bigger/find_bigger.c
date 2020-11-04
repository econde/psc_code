int find_bigger(int array[], size_t array_size) {
	int bigger = array[0];
	for (size_t i = 1; i < array_size; ++i)
		if (array[i] > bigger)
			bigger = array[i];
	return bigger;
}
