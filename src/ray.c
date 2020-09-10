/*
 * The math for this is beautiful
 * Watch: https://www.youtube.com/watch?v=eOCQfxRQ2pY
 * Read: https://lodev.org/cgtutor/raycasting.html
 */
#include <math.h>
#include <stddef.h>
#include <sys/types.h>
#include "../libs/radix/src/radix.h"

#include "camera.h"
#include "ray.h"
#include "scene.h"

struct SurcRayHitInfo
surc_raycast_until_collision(const struct SurcVect2f pos,
                             const struct SurcVect2f rayDir,
                             struct SurcScene *const scene)
{
	struct SurcVect2i step;
	struct SurcVect2f sideDist, deltaDist;

	struct SurcRayHitInfo hitInfo;

	hitInfo.map.x = (int)pos.x;
	hitInfo.map.y = (int)pos.y;

	/* Calculate deltas */
	deltaDist.x = fabsf(1/rayDir.x);
	deltaDist.y = fabsf(1/rayDir.y);

	/* step and sideDists (offsets) */
	if (rayDir.x < 0) {
		step.x = -1;
		sideDist.x = (pos.x - hitInfo.map.x)*deltaDist.x;
	} else {
		step.x = 1;
		sideDist.x = (hitInfo.map.x + 1 - pos.x)*deltaDist.x;
	}

	if (rayDir.y < 0) {
		step.y = -1;
		sideDist.y = (pos.y - hitInfo.map.y)*deltaDist.y;
	} else {
		step.y = 1;
		sideDist.y = (hitInfo.map.y + 1 - pos.y)*deltaDist.y;
	}

	/* DDA */
	for (;;) {
		if (sideDist.x < sideDist.y) {
			sideDist.x += deltaDist.x;
			hitInfo.map.x += step.x;
			hitInfo.isNS = true;
		} else {
			sideDist.y += deltaDist.y;
			hitInfo.map.y += step.y;
			hitInfo.isNS = false;
		}

		if (surc_scene_get_tile(scene, hitInfo.map.x, hitInfo.map.y) > 0) {
			if (hitInfo.isNS)
				hitInfo.dist = (hitInfo.map.x - pos.x + (1 - step.x)/2)/rayDir.x;
			else
				hitInfo.dist = (hitInfo.map.y - pos.y + (1 - step.y)/2)/rayDir.y;

			return hitInfo;
		}
	}
}
