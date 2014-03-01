#ifndef BOUNDARIES_H
#define BOUNDARIES_H

struct ghostbox{
    double shiftx;
    double shifty;
    double shiftz;
    double shiftvx;
    double shiftvy;
    double shiftvz;
};


// collision with some close boundaries
void boundaries_collision(struct particle pt, int id_boundaries);

// check if any particle has left the main box.
void boundaries_check();

// create ghostbox, index in 3D direction
struct ghostbox boundaries_get_ghostbox(int i, int j, int k);

// number of ghostboxes in a direction
extern int nghostx;
extern int nghosty;
extern int nghostz;


#endif
