#include "taylor.h"

#include <math.h>

static double sin_term(double x, int index, double previous_term,
                       void *context) {
    (void)context;
    double reduced_x = remainder(x, 2.0 * TAYLOR_PI);

    if (index == 0) {
        return reduced_x;
    }

    return -previous_term * reduced_x * reduced_x /
           ((2.0 * index) * (2.0 * index + 1.0));
}

static double sin_error(double x, int terms, double approximation,
                        void *context) {
    (void)terms;
    (void)context;
    return fabs(sin(x) - approximation);
}

double sin_taylor(double x, int terms) {
    if (terms <= 0) {
        return 0.0;
    }
    return taylor_sum(x, terms, sin_term, NULL);
}

double sin_precision(double x, int terms) {
    return sin_error(x, terms, sin_taylor(x, terms), NULL);
}

const TaylorFunction sin_function = {
    "sin(x)", sin, sin_term, sin_error
};
