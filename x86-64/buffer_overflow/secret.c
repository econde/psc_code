#include <stdio.h>
#include <string.h>

void print_secret(int n) {
	static const char *secret[] = {
		"Tfhsfep!ef!qpmjdijofmp\v",
		"Ugitgfq\"fg\"cdgnjc\f",
		"Vhjuhgr#gh#Idwlpd"
	};
	const char *s = secret[n - 1];
	while (*s)
		putchar(*s++ - n);
}

void secrets() {
	struct {
		int a;
		char buffer[7];
		short b;
	} x;

	x.a = 'a';
	x.b = 'b';

	gets(x.buffer);
	
	if (x.b == 'B')
		print_secret(1);

	if (x.a == 'A')
		print_secret(2);
}

int main() {
	printf("Secrets\n");
	secrets();
}
