#include <stdio.h>

long call_proc();

int main() {
	long aux =  call_proc();
	printf("call_func = %ld\n", aux);
}
