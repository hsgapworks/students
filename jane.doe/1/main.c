#include <stdio.h>

double wardrobe_mass(double h, double w, double d,
                     double chipboard, double fiberboard, double wood);
int shelf_count(double h);

static int read_value(const char *prompt, double *value)
{
    printf("%s", prompt);
    if (scanf("%lf", value) != 1) {
        printf("Input error\n");
        return 0;
    }
    return 1;
}

int main(void)
{
    double h, w, d, chipboard, fiberboard, wood;

    if (!read_value("Height h (cm, 180-220): ", &h) ||
        !read_value("Width w (cm, 80-120): ", &w) ||
        !read_value("Depth d (cm, 50-90): ", &d) ||
        !read_value("Chipboard density (kg/m3): ", &chipboard) ||
        !read_value("Fiberboard density (kg/m3): ", &fiberboard) ||
        !read_value("Wood density (kg/m3): ", &wood)) {
        return 1;
    }

    if (h < 180.0 || h > 220.0 || w < 80.0 || w > 120.0 ||
        d < 50.0 || d > 90.0 ||
        chipboard <= 0.0 || fiberboard <= 0.0 || wood <= 0.0) {
        printf("Value out of range\n");
        return 1;
    }

    printf("Shelves: %d\n", shelf_count(h));
    printf("Wardrobe mass: %.3f kg\n",
           wardrobe_mass(h, w, d, chipboard, fiberboard, wood));

    return 0;
}
