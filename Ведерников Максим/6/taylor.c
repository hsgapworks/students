#include "taylor.h"

#include <math.h>

double taylor_sum(double x, int terms, TaylorTermFunction term, void *context) {
    double sum = 0.0;
    double previous_term = 0.0;

    for (int i = 0; i < terms; i++) {
        double current_term = term(x, i, previous_term, context);
        sum += current_term;
        previous_term = current_term;
    }

    return sum;
}

TaylorResult taylor_calculate(double x, double tolerance, int max_terms,
                              TaylorTermFunction term,
                              TaylorErrorFunction estimate_error,
                              void *context) {
    TaylorResult result;
    double previous_term = 0.0;

    result.terms = 1;
    previous_term = term(x, 0, previous_term, context);
    result.value = previous_term;
    result.error = estimate_error(x, result.terms, result.value, context);

    while ((!isfinite(result.error) || result.error > tolerance) &&
           result.terms < max_terms) {
        previous_term = term(x, result.terms, previous_term, context);
        result.value += previous_term;
        result.terms++;
        result.error = estimate_error(x, result.terms, result.value, context);
    }

    return result;
}
