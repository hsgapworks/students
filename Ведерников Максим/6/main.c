#include "taylor.h"

#include <math.h>
#include <stdio.h>

static const TaylorFunction *functions[] = {
    &exp_function,
    &sin_function,
    &cos_function,
    &csc_function
};

static const TaylorFunction *select_function(void) {
    int choice;

    printf("Choose function:\n");
    printf("0 - exp(x)\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - csc(x)\n");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice\n");
        return NULL;
    }

    if (choice < 0 || choice > 3) {
        printf("Invalid choice\n");
        return NULL;
    }

    return functions[choice];
}

static int read_x(double *x) {
    printf("Enter x: ");
    if (scanf("%lf", x) != 1) {
        printf("Invalid x value\n");
        return 0;
    }
    if (!isfinite(*x)) {
        printf("x must be a finite number\n");
        return 0;
    }

    return 1;
}

static int get_reference_value(const TaylorFunction *function, double x,
                               double *actual) {
    if (function == &csc_function && csc_is_singular(x)) {
        printf("csc(x) is undefined for this x\n");
        return 0;
    }

    *actual = function->reference(x);
    if (!isfinite(*actual)) {
        printf("The reference value is outside the representable range.\n");
        return 0;
    }

    return 1;
}

static int run_mode_1(const TaylorFunction *function, double x,
                      double actual) {
    double tolerance;
    int max_terms;

    printf("Enter calculation tolerance (at least 0.000001): ");
    if (scanf("%lf", &tolerance) != 1) {
        printf("Invalid precision\n");
        return 1;
    }

    if (!isfinite(tolerance) || tolerance < 0.000001) {
        printf("Tolerance must be a finite number greater than or equal to 0.000001\n");
        return 1;
    }

    printf("Enter maximum number of terms (1-1000): ");
    if (scanf("%d", &max_terms) != 1) {
        printf("Invalid maximum number of terms\n");
        return 1;
    }

    if (max_terms < 1 || max_terms > MAX_TAYLOR_TERMS) {
        printf("Maximum number of terms must be between 1 and 1000\n");
        return 1;
    }

    TaylorResult result = taylor_calculate(
        x, tolerance, max_terms, function->term, function->estimate_error,
        NULL);

    printf("\nFunction: %s\n", function->name);
    printf("Requested tolerance: %.12g\n", tolerance);
    printf("Maximum terms: %d\n", max_terms);
    printf("Terms used: %d\n", result.terms);
    printf("Taylor result: %.12g\n", result.value);
    printf("Reference value: %.12g\n", actual);
    printf("Absolute error: %.12g\n", result.error);

    if (!isfinite(result.error) || result.error > tolerance) {
        printf("Tolerance was not reached before the maximum number of terms.\n");
    } else {
        printf("Requested tolerance reached.\n");
    }

    return 0;
}

static int run_mode_2(const TaylorFunction *function, double x,
                      double actual) {
    int n_max;

    printf("Enter number of experiments (1-25): ");
    if (scanf("%d", &n_max) != 1) {
        printf("Invalid number of experiments\n");
        return 1;
    }

    if (n_max < 1 || n_max > 25) {
        printf("Number of experiments must be between 1 and 25\n");
        return 1;
    }

    printf("\nFunction: %s\n", function->name);
    printf("Reference value: %.12g\n", actual);
    printf("%-16s %-28s %-28s\n",
           "Number of terms", "Approximated function value",
           "Difference from reference");

    for (int terms = 1; terms <= n_max; terms++) {
        double approximation = taylor_sum(x, terms, function->term, NULL);
        double difference = fabs(approximation - actual);

        printf("%-16d %-28.12g %-28.12g\n",
               terms, approximation, difference);
    }

    return 0;
}

int main(void) {
    int mode;
    double x;
    double actual;

    printf("Choose mode:\n");
    printf("1 - Tolerance-based calculation\n");
    printf("2 - Serial experiment\n");
    if (scanf("%d", &mode) != 1) {
        printf("Invalid mode\n");
        return 1;
    }
    if (mode != 1 && mode != 2) {
        printf("Invalid mode\n");
        return 1;
    }

    const TaylorFunction *function = select_function();
    if (function == NULL || !read_x(&x) ||
        !get_reference_value(function, x, &actual)) {
        return 1;
    }

    if (mode == 2) {
        return run_mode_2(function, x, actual);
    }

    return run_mode_1(function, x, actual);
}
