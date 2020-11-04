/*
	n = 64 provoca overflow
*/

long getbits(long x, int p, int n) {
    return (x >> p) & ((1L << n) - 1);
}

