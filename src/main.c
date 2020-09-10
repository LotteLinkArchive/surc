#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>
#include <sys/types.h>
#include "../libs/surrender/src/surrender.h"

#include "camera.h"
#include "ray.h"
#include "render.h"
#include "scene.h"

#define WIDTH 800
#define HEIGHT 600

#define TILE_SIZE 64

#define MAP_X 10
#define MAP_Y 10
const uint8_t map[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.25

SR_Canvas overlay; /* Overlay canvas to draw 2d representation */
SR_Canvas frame; /* Raycast render */

struct SurcCamera camera;
struct SurcScene scene; /* Test scene */

int
init(SR_Canvas *canvas)
{
	/* Init camera */
	camera.pos.x = MAP_X/2;
	camera.pos.y = MAP_Y/2;
	camera.dir.x = 1;
	camera.cameraPlane.y = 0.66f;
	camera.height = TILE_SIZE;

	overlay = SR_NewCanvas(MAP_X*OVERLAY_TILE_SIZE, MAP_Y*OVERLAY_TILE_SIZE);
	if (!SR_CanvasIsValid(&overlay))
		return 1;

	frame = SR_NewCanvas(canvas->width, canvas->height);
	if (!SR_CanvasIsValid(&frame))
		return 1;

	if (!surc_scene_new(&scene, MAP_X, MAP_Y, 2))
		return 1;

	surc_scene_load(&scene, map);
	return 0;
}

int
update(SR_Canvas *canvas)
{
	/* render frame */
	SR_DrawRect(&frame, SR_CreateRGBA(0, 0, 0, 255), 0, 0, frame.width, frame.height);
	surc_render_frame(&frame, &scene, &camera);
	SR_MergeCanvasIntoCanvas(canvas, &frame, 0, 0, 255, SR_BLEND_REPLACE);

	/* update overlay */
	surc_render_overlay(&overlay, &scene, &camera);
	SR_MergeCanvasIntoCanvas(canvas, &overlay, 0, 0, 255, SR_BLEND_REPLACE);
	return 0;
}

void
onKeyDown(SDL_KeyCode key)
{
	float oldX;

	/* Camera movement and rotation */
	if (key == SDLK_UP) {
		camera.pos.x += camera.dir.x * MOVE_SPEED;
		camera.pos.y += camera.dir.y * MOVE_SPEED;
	}
	if (key == SDLK_DOWN) {
		camera.pos.x -= camera.dir.x * MOVE_SPEED;
		camera.pos.y -= camera.dir.y * MOVE_SPEED;
	}
	if (key == SDLK_LEFT) {
		oldX = camera.dir.x;
		camera.dir.x = camera.dir.x*cosf(-ROT_SPEED) - camera.dir.y*sinf(-ROT_SPEED);
		camera.dir.y = oldX*sinf(-ROT_SPEED) + camera.dir.y*cosf(-ROT_SPEED);
		oldX = camera.cameraPlane.x;
		camera.cameraPlane.x = camera.cameraPlane.x*cosf(-ROT_SPEED) - camera.cameraPlane.y*sinf(-ROT_SPEED);
		camera.cameraPlane.y = oldX*sinf(-ROT_SPEED) + camera.cameraPlane.y*cosf(-ROT_SPEED);
	}
	if (key == SDLK_RIGHT) {
		oldX = camera.dir.x;
		camera.dir.x = camera.dir.x*cosf(ROT_SPEED) - camera.dir.y*sinf(ROT_SPEED);
		camera.dir.y = oldX*sinf(ROT_SPEED) + camera.dir.y*cosf(ROT_SPEED);
		oldX = camera.cameraPlane.x;
		camera.cameraPlane.x = camera.cameraPlane.x*cosf(ROT_SPEED) - camera.cameraPlane.y*sinf(ROT_SPEED);
		camera.cameraPlane.y = oldX*sinf(ROT_SPEED) + camera.cameraPlane.y*cosf(ROT_SPEED);
	}

	/* printf("x: %.2f y: %0.2f", camera.dir.x, camera.dir.y); */
}

void
clean()
{
	surc_scene_free(&scene);
	SR_DestroyCanvas(&overlay);
}

int
main(int argc, char **argv)
{
	SR_Canvas canvas;
	SDL_Window *window;
	SDL_Event ev;

	SDL_Surface *wsurf, *csurf;

	int status = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		status = 1;
		goto retstatus;
	}

	if (!(window = SDL_CreateWindow(
		"SURC Shall Not SurRender!",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		0
	))) {
		status = 2;
		goto sdl_quit;
	}

	canvas = SR_NewCanvas(WIDTH, HEIGHT);
	if (!SR_CanvasIsValid(&canvas)) {
		status = 3;
		goto sdl_destroywin;
	}

	SR_DrawRect(&canvas, SR_CreateRGBA(0, 0, 0, 255), 0, 0, canvas.width, canvas.height);

	if (!(csurf = SDL_CreateRGBSurfaceFrom(
		canvas.pixels,
		canvas.width,
		canvas.height,
		32,
		canvas.width*sizeof(SR_RGBAPixel),
		0x000000FF,
		0x0000FF00,
		0x00FF0000,
		0xFF000000
	))) {
		status = 4;
		goto sr_destroycanvas;
	}

	if (!(wsurf = SDL_GetWindowSurface(window))) {
		status = 5;
		goto sdl_freesurf;
	}

	/* Allow one time init */
	if (init(&canvas)) {
		status = 6;
		goto sdl_freesurf;
	}

event_loop:
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT: goto surc_clean_mess;
		case SDL_KEYDOWN: onKeyDown(ev.key.keysym.sym);
		}
	}

	/* Update code here */
	if (update(&canvas)) {
		status = 7;
		goto surc_clean_mess;
	}

	if (SDL_BlitSurface(csurf, NULL, wsurf, NULL) < 0) {
		status = 8;
		goto surc_clean_mess;
	}

	if (SDL_UpdateWindowSurface(window) < 0) {
		status = 9;
		goto surc_clean_mess;
	}

	goto event_loop;

surc_clean_mess:
	clean();
sdl_freesurf:
	SDL_FreeSurface(csurf);
sr_destroycanvas:
	SR_DestroyCanvas(&canvas);
sdl_destroywin:
	SDL_DestroyWindow(window);
sdl_quit:
	SDL_Quit();
retstatus:
	return status;
}
