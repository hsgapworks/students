#define CM_PER_M 100.0
#define BACK_THICKNESS_M 0.005
#define PANEL_THICKNESS_M 0.015
#define DOOR_THICKNESS_M 0.010
#define SHELF_STEP_CM 40.0

int shelf_count(double h)
{
    return (int)(h / SHELF_STEP_CM);
}

static double volume_m3(double a_cm, double b_cm, double thickness_m)
{
    return (a_cm / CM_PER_M) * (b_cm / CM_PER_M) * thickness_m;
}

double wardrobe_mass(double h, double w, double d,
                     double chipboard, double fiberboard, double wood)
{
    double v_back = volume_m3(h, w, BACK_THICKNESS_M);
    double v_sides = 2.0 * volume_m3(h, d, PANEL_THICKNESS_M);
    double v_caps = 2.0 * volume_m3(w, d, PANEL_THICKNESS_M);
    double v_doors = volume_m3(h, w, DOOR_THICKNESS_M);
    double v_shelves = (double)shelf_count(h) * volume_m3(w, d, PANEL_THICKNESS_M);

    return v_back * fiberboard + (v_sides + v_caps + v_shelves) * chipboard
           + v_doors * wood;
}
