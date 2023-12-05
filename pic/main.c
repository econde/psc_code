extern int lib_var;
void lib_func1();
void lib_func2();

int prog_var = 4;

int prog_func() {
	return prog_var + lib_var;
}

int main() {
	lib_func1();
	lib_func2();
	return prog_func();
}
