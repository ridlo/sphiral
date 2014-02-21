#ifndef BOUNDARIES_H
#define BOUNDARIES_H

struct ghostbox{
    float shiftx;
    float shifty;
    float shiftz;
    float shiftvx;
    float shiftvy;
    float shiftvz;
}

// check if any particle has left the main box.
void boundaries_check();

// create ghostbox, index in 3D direction
struct ghostbox boundaries_get_ghostbox(int i, int j, int k);

// number of ghostboxes in a direction
extern int nghostx;
extern int nghosty;
extern int nghostz;

#endif
