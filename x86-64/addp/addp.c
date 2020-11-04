int add(int a, int b);

void addp(int *op1, int *op2, int *res) {
	*res = add(*op1, *op2);
}

