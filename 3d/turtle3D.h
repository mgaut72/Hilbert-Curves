#ifndef H_TURTLE_3D
#define H_TURTLE_3D

typedef struct {
    int heading[3];
    int left[3];
    int up[3];
} orientation3D;

extern const orientation3D default_orientation3D;

orientation3D turn_left(orientation3D o);
orientation3D turn_right(orientation3D o);
orientation3D pitch_down(orientation3D o);
orientation3D pitch_up(orientation3D o);
orientation3D roll_left(orientation3D o);
orientation3D roll_right(orientation3D o);
orientation3D turn_around(orientation3D o);

#endif
