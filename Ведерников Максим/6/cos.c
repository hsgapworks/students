#include "taylor.h"

#include <math.h>

static double cos_term(double x, int index, double previous_term,
                       void *context) {
    (void)context;
    double reduced_x = remainder(x, 2.0 * TAYLOR_PI);

    if (index == 0) {
        return 1.0;
    }

    return -previous_term * reduced_x * reduced_x /
           ((2.0 * index - 1.0) * (2.0 * index));
}

static double cos_error(double x, int terms, double approximation,
                        void *context) {
    (void)terms;
    (void)context;
    return fabs(cos(x) - approximation);
}

double cos_taylor(double x, int terms) {
    if (terms <= 0) {
        return 1.0;
    }
    return taylor_sum(x, terms, cos_term, NULL);
}

double cos_precision(double x, int terms) {
    return cos_error(x, terms, cos_taylor(x, terms), NULL);
}

const TaylorFunction cos_function = {
    "cos(x)", cos, cos_term, cos_error
};
