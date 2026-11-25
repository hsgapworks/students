#ifndef TAYLOR_H
#define TAYLOR_H

#define MAX_TAYLOR_TERMS 1000
#define TAYLOR_PI 3.14159265358979323846

typedef double (*TaylorTermFunction)(double x, int index,
                                     double previous_term, void *context);
typedef double (*TaylorErrorFunction)(double x, int terms,
                                      double approximation, void *context);

typedef struct {
    double value;
    double error;
    int terms;
} TaylorResult;

typedef struct {
    const char *name;
    double (*reference)(double x);
    TaylorTermFunction term;
    TaylorErrorFunction estimate_error;
} TaylorFunction;

double taylor_sum(double x, int terms, TaylorTermFunction term, void *context);
TaylorResult taylor_calculate(double x, double tolerance, int max_terms,
                              TaylorTermFunction term,
                              TaylorErrorFunction estimate_error,
                              void *context);

double exp_taylor(double x, int terms);
double sin_taylor(double x, int terms);
double cos_taylor(double x, int terms);
double csc_taylor(double x, int terms);

double exp_precision(double x, int terms);
double sin_precision(double x, int terms);
double cos_precision(double x, int terms);
double csc_precision(double x, int terms);

int csc_is_singular(double x);

extern const TaylorFunction exp_function;
extern const TaylorFunction sin_function;
extern const TaylorFunction cos_function;
extern const TaylorFunction csc_function;

#endif
