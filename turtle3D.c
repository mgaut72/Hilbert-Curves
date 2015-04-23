#include "turtle3D.h"

orientation3D turn_left(orientation3D o){
    orientation3D new = o;
    new.heading[0] = o.left[0];
    new.heading[1] = o.left[1];
    new.heading[2] = o.left[2];
    new.left[0] = -1 * o.heading[0];
    new.left[1] = -1 * o.heading[1];
    new.left[2] = -1 * o.heading[2];
    return new;
}

orientation3D turn_right(orientation3D o){
    orientation3D new = o;
    new.left[0] = o.heading[0];
    new.left[1] = o.heading[1];
    new.left[2] = o.heading[2];
    new.heading[0] = -1 * o.left[0];
    new.heading[1] = -1 * o.left[1];
    new.heading[2] = -1 * o.left[2];
    return new;
}

orientation3D pitch_down(orientation3D o){
    orientation3D new = o;
    new.heading[0] = -1 * o.up[0];
    new.heading[1] = -1 * o.up[1];
    new.heading[2] = -1 * o.up[2];
    new.up[0] = o.heading[0];
    new.up[1] = o.heading[1];
    new.up[2] = o.heading[2];
    return new;
}

orientation3D pitch_up(orientation3D o){
    orientation3D new = o;
    new.up[0] = -1 * o.heading[0];
    new.up[1] = -1 * o.heading[1];
    new.up[2] = -1 * o.heading[2];
    new.heading[0] = o.up[0];
    new.heading[1] = o.up[1];
    new.heading[2] = o.up[2];
    return new;
}

orientation3D roll_left(orientation3D o){
    orientation3D new = o;
    new.left[0] = -1 * o.up[0];
    new.left[1] = -1 * o.up[1];
    new.left[2] = -1 * o.up[2];
    new.up[0] = o.left[0];
    new.up[1] = o.left[1];
    new.up[2] = o.left[2];
    return new;
}

orientation3D roll_right(orientation3D o){
    orientation3D new = o;
    new.up[0] = -1 * o.left[0];
    new.up[1] = -1 * o.left[1];
    new.up[2] = -1 * o.left[2];
    new.left[0] = o.up[0];
    new.left[1] = o.up[1];
    new.left[2] = o.up[2];
    return new;
}

orientation3D turn_around(orientation3D o){
    return turn_left(turn_left(o));
}
