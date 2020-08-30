#ifndef SURC_RAY_H
#define SURC_RAY_H

#include "camera.h"
#include "scene.h"

/*
 * Efficiently calculates a ray collision using DDA
 * returns the distance to the hit
 */
float
surc_raycast_until_collision(const struct SurcVect2f pos,
                             const struct SurcVect2f rayDir,
                             struct SurcScene *const scene);

#endif
