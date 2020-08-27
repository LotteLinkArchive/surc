#include <SDL2/SDL.h>
#include <stdint.h>
#include "../libs/surrender/src/surrender.h"

#include "scene.h"

#define WIDTH 1280
#define HEIGHT 720

#define TILE_SIZE 64
#define OVERLAY_TILE_SIZE 16

#define MAP_X 5
#define MAP_Y 5
const uint8_t map[] = {
	1, 1, 1, 1, 1,
	1, 0, 0, 0, 1,
	1, 0, 1, 0, 1,
	1, 0, 0, 0, 1,
	1, 1, 1, 1, 1
};

SR_Canvas overlay; /* Overlay canvas to draw 2d representation */

struct SurcScene scene; /* Test scene */

int
init(SR_Canvas *canvas)
{
	SR_RGBAPixel color;
	uint8_t x, y;

	overlay = SR_NewCanvas(canvas->width, canvas->height);
	if (!SR_CanvasIsValid(&overlay))
		return 1;

	SR_DrawRect(&overlay, SR_CreateRGBA(255, 255, 255, 255), 0, 0, overlay.width/4, overlay.height/4);

	if (!surc_scene_new(&scene, MAP_X, MAP_Y))
		return 1;

	surc_scene_load(&scene, map);
	for (y = 0; y < scene.height; ++y)
	for (x = 0; x < scene.width; ++x)
	{
		switch (surc_scene_get_tile(&scene, x, y)) {
		case 1:
			color = SR_CreateRGBA(0, 255, 0, 255);
			break;
		default:
			color = SR_CreateRGBA(255, 255, 255, 255);
		}

		SR_DrawRect(&overlay, color, x*OVERLAY_TILE_SIZE, y*OVERLAY_TILE_SIZE, OVERLAY_TILE_SIZE, OVERLAY_TILE_SIZE);
	}

	SR_MergeCanvasIntoCanvas(canvas, &overlay, 0, 0, 255, SR_BLEND_REPLACE);
	return 0;
}

int
update(SR_Canvas *canvas)
{
	return 0;
}

void
clean()
{
	SR_DestroyCanvas(&overlay);
}

int
main(int argc, char **argv)
{
	SR_Canvas canvas;
	SDL_Window *window;
	SDL_Event ev;

	SDL_Surface *wsurf, *csurf;

	int status;

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
	while (SDL_PollEvent(&ev))
		if (ev.type == SDL_QUIT)
			goto surc_clean_mess;

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
