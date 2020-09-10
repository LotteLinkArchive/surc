#include "render.h"

#include "camera.h"
#include "ray.h"
#include "scene.h"

void
surc_render_frame(SR_Canvas *canvas,
                  struct SurcScene *const scene,
                  struct SurcCamera *const camera)
{
	int lineHeight, lineStart, lineEnd;
	float cameraX;
	SR_Canvas texture;
	SR_RGBAPixel color;
	struct SurcVect2f rayDir;
	struct SurcRayHitInfo hitInfo;
	unsigned short i;

	/* Shoot rays */
	for (i = 0; i < canvas->width; ++i) {
		cameraX = 2*i/(float)canvas->width-1;
		rayDir.x = camera->dir.x + camera->cameraPlane.x*cameraX;
		rayDir.y = camera->dir.y + camera->cameraPlane.y*cameraX;

		hitInfo = surc_raycast_until_collision(camera->pos, rayDir, scene);
		
		/* Calculate line points */
		lineHeight = (int)(canvas->height/hitInfo.dist);
		lineStart = -lineHeight/2 + canvas->height/2;
		if (lineStart < 0)
			lineStart = 0;

		lineEnd = lineHeight/2 + canvas->height/2;
		if (lineEnd >= canvas->height)
			lineEnd = canvas->height - 1;

		texture = surc_scene_get_texture(scene, hitInfo.map.x, hitInfo.map.y);
		if (!SR_CanvasIsValid(&texture)) {
			color = hitInfo.isNS ? SR_CreateRGBA(255, 255, 255, 255) : SR_CreateRGBA(200, 200, 200, 255);

			SR_DrawRect(canvas, color, i, lineStart, 1, lineEnd - lineStart);
		}
	}
}

void
surc_render_overlay(SR_Canvas *canvas,
                    struct SurcScene *const scene,
                    struct SurcCamera *const camera)
{
	SR_RGBAPixel color;
	uint8_t x, y;
	struct SurcVect2f canvasPos;

	SR_DrawRect(canvas, SR_CreateRGBA(255, 255, 255, 255), 0, 0, canvas->width, canvas->height);
	for (y = 0; y < scene->height; ++y)
	for (x = 0; x < scene->width; ++x)
	{
		switch (surc_scene_get_tile(scene, x, y)) {
		case 1:
			color = SR_CreateRGBA(0, 255, 0, 255);
			break;
		default:
			color = SR_CreateRGBA(255, 255, 255, 255);
		}

		SR_DrawRect(canvas, color, x*OVERLAY_TILE_SIZE, y*OVERLAY_TILE_SIZE, OVERLAY_TILE_SIZE, OVERLAY_TILE_SIZE);
	}

	/* Camera */
	canvasPos.x = camera->pos.x*OVERLAY_TILE_SIZE;
	canvasPos.y = camera->pos.y*OVERLAY_TILE_SIZE;

	SR_DrawRect(canvas, SR_CreateRGBA(100, 0, 0, 255), canvasPos.x - CAMERA_SIZE/2, canvasPos.y - CAMERA_SIZE/2, CAMERA_SIZE, CAMERA_SIZE);
	SR_DrawLine(canvas, SR_CreateRGBA(100, 0, 100, 255), canvasPos.x, canvasPos.y, canvasPos.x + camera->dir.x*DIR_VECTOR_LEN, canvasPos.y + camera->dir.y*DIR_VECTOR_LEN);
}
