#include "taylor.h"

#include <math.h>

static double exp_term(double x, int index, double previous_term,
                       void *context) {
    (void)context;
    if (index == 0) {
        return 1.0;
    }
    return previous_term * x / index;
}

static double exp_error(double x, int terms, double approximation,
                        void *context) {
    (void)terms;
    (void)context;
    return fabs(exp(x) - approximation);
}

double exp_taylor(double x, int terms) {
    if (terms <= 0) {
        return 1.0;
    }
    return taylor_sum(x, terms, exp_term, NULL);
}

double exp_precision(double x, int terms) {
    return exp_error(x, terms, exp_taylor(x, terms), NULL);
}

const TaylorFunction exp_function = {
    "exp(x)", exp, exp_term, exp_error
};
