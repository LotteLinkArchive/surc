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
	/* float offsetX, offsetY; /1* offset from absolute grid position *1/ */
	/* float stepX, stepY; /1* step between each edge hit *1/ */
	/* float interceptX, interceptY; /1* difference to first hit *1/ */

	/* /1* calculate offsets *1/ */
	/* offsetX = modf(camera->pos.x, NULL); */
	/* offsetY = modf(camera->pos.y, NULL); */

	/* /1* steps *1/ */
	/* stepX = tan(camera->yaw); */
	/* stepY = atan(camera->yaw); */

	/* /1* intercepts *1/ */
	/* interceptX = camera->pos.x - offsetY/tan(camera->yaw); */
	/* interceptX = camera->pos.x + offsetX/tan(camera->yaw); */
	return 0;
}
