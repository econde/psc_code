#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s libXXX.so\n", argv[0]);
		return -1;
	}

	void* handle = dlopen(argv[1], RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return -1;
	}

	int (*f)(void) = dlsym(handle, "lib_func");
	if (f == NULL) {
		fprintf(stderr, "Could not find lib_func: %s\n", dlerror());
		return -1;
	}

	printf("Calling lib_func\n");
	int ret = f();
	printf("lib_func returned %d\n", ret);

	if (dlclose(handle) != 0) {
		fprintf(stderr, "Could not close plugin: %s\n", dlerror());
		return -1;
	}
	return 0;
}
