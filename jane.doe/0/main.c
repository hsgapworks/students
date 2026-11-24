#include <stdio.h>
#include <math.h>

#define EPS 1e-9

int main(void)
{
    double x1, y1, r1, x2, y2, r2;

    printf("Enter x1 y1 r1 x2 y2 r2: ");
    if (scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2) != 6) {
        printf("Input error\n");
        return 1;
    }
    if (r1 < 0.0 || r2 < 0.0) {
        printf("Radius must not be negative\n");
        return 1;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx * dx + dy * dy);
    double sum = r1 + r2;
    double diff = fabs(r1 - r2);

    if (d < EPS && diff < EPS) {
        printf("Circles coincide\n");
    } else if (d > sum + EPS) {
        printf("Circles are separate\n");
    } else if (fabs(d - sum) <= EPS) {
        printf("External tangency\n");
    } else if (d > diff + EPS) {
        printf("Circles intersect at two points\n");
    } else if (fabs(d - diff) <= EPS) {
        printf("Internal tangency\n");
    } else {
        printf("One circle inside the other, no intersections\n");
    }

    return 0;
}
