#ifndef SURC_RAY_H
#define SURC_RAY_H

#include "camera.h"
#include "scene.h"

/*
 * Efficiently calculates a ray collision using DDA
 * returns 0 on success, 1 on failure
 */
int
surc_raycast_until_collision(struct SurcVect2f *const hit,
                             const struct SurcVect2f pos,
                             const struct SurcVect2f rayDir,
                             struct SurcScene *const scene);

#endif
