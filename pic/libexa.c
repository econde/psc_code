extern int prog_var;

int prog_func();

int lib_var = 3;

void lib_func1() {
	lib_var = prog_var;
	prog_var = prog_func();
}

void lib_func2() {
}
