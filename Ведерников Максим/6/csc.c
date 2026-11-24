#include "taylor.h"

#include <math.h>

static double coefficients[MAX_TAYLOR_TERMS];
static int coefficients_initialized;

static void initialize_coefficients(void) {
    if (coefficients_initialized) {
        return;
    }

    coefficients[0] = 1.0;
    for (int k = 1; k < MAX_TAYLOR_TERMS; k++) {
        double inverse_factorial = 1.0;
        double coefficient = 0.0;
        for (int j = 1; j <= k; j++) {
            inverse_factorial /= (2.0 * j - 1.0) * (2.0 * j);
            double sign = j % 2 == 1 ? 1.0 : -1.0;
            coefficient += sign * coefficients[k - j] * inverse_factorial;
        }
        coefficients[k] = coefficient;
    }

    coefficients_initialized = 1;
}

static double csc_reference(double x) {
    return 1.0 / sin(x);
}

static double csc_term(double x, int index, double previous_term,
                       void *context) {
    (void)context;
    if (index < 0 || index >= MAX_TAYLOR_TERMS) {
        return 0.0;
    }

    initialize_coefficients();

    double reduced_x = remainder(x, 2.0 * TAYLOR_PI);
    double sign = reduced_x < 0.0 ? -1.0 : 1.0;
    double t = fabs(reduced_x) - TAYLOR_PI / 2.0;

    if (index == 0) {
        return sign;
    }

    return previous_term * coefficients[index] / coefficients[index - 1] *
           t * t;
}

static double csc_error(double x, int terms, double approximation,
                        void *context) {
    (void)terms;
    (void)context;
    return fabs(csc_reference(x) - approximation);
}

int csc_is_singular(double x) {
    return fabs(sin_taylor(x, MAX_TAYLOR_TERMS)) < 1e-12;
}

double csc_taylor(double x, int terms) {
    if (terms < 1 || csc_is_singular(x)) {
        return NAN;
    }
    if (terms > MAX_TAYLOR_TERMS) {
        terms = MAX_TAYLOR_TERMS;
    }
    return taylor_sum(x, terms, csc_term, NULL);
}

double csc_precision(double x, int terms) {
    return csc_error(x, terms, csc_taylor(x, terms), NULL);
}

const TaylorFunction csc_function = {
    "csc(x)", csc_reference, csc_term, csc_error
};
