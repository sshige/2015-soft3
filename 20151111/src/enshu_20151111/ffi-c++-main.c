#include <stdio.h>

double sinc(double x);

int main () {
    double f = 1.0;
    fprintf(stderr, "sinc(%f) = %f\n", f, sinc(f));
    return 0;
}
