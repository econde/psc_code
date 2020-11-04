void proc(long a1, long *a1p, int a2, int *a2p,
			short a3, short *a3p, char a4, char *a4p);

#if 1
long call_proc2() {
	long x1 = 1;
	int x2 = 2;
	short x3 = 3;
	char x4 = -4;

	func(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
	return (x1 + x2) * (x3 - x4);
}
#endif

#if 0

long x1 = 1;
int x2 = 2;
short x3 = 3;
char x4 = -4;

long call_proc1() {
	func(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
	return (x1 + x2) * (x3 - x4);
}
#endif
