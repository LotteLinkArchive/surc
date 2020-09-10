#ifndef SURC_RAY_H
#define SURC_RAY_H

#include "../libs/radix/src/radix.h"

#include "camera.h"
#include "scene.h"

struct SurcRayHitInfo {
	struct SurcVect2i map;
	float dist;
	bool isNS; /* else EW hit */
};

/*
 * Efficiently calculates a ray collision using DDA
 * returns the distance to the hit
 */
struct SurcRayHitInfo
surc_raycast_until_collision(const struct SurcVect2f pos,
                             const struct SurcVect2f rayDir,
                             struct SurcScene *const scene);

#endif
