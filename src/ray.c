/*
 * The math for this is beautiful
 * Watch: https://www.youtube.com/watch?v=eOCQfxRQ2pY
 * Read: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
 */
#include <math.h>
#include <stddef.h>

#include "camera.h"
#include "ray.h"
#include "scene.h"

int
surc_raycast_until_collision(const struct SurcVect2 *hit,
                             const struct SurcCamera *const camera,
                             const struct SurcScene *const scene)
{
	float offsetX, offsetY; /* offset from absolute grid position */
	float stepX, stepY; /* step between each edge hit */
	float interceptX, interceptY; /* difference to first hit */

	/* calculate offsets */
	offsetX = modf(camera->pos.x, NULL);
	offsetY = modf(camera->pos.y, NULL);

	/* steps */
	stepX = tan(camera->yaw);
	stepY = atan(camera->yaw);

	/* intercepts */
	interceptX = camera->pos.x - offsetY/tan(camera->yaw);
	interceptX = camera->pos.x + offsetX/tan(camera->yaw);
}
