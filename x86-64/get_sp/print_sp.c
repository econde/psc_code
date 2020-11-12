#include <stdio.h>

unsigned long get_sp();

void recurse() {
	char array[1024*1024];
	printf("%lx\n", get_sp());
	recurse();
}

int main() {
	recurse();
}
