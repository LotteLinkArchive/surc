#include <stdio.h>

#include <SDL2/SDL.h>
#include "../libs/surrender/src/surrender.h"

#define WIDTH 640
#define HEIGHT 480

void
init(SR_Canvas *canvas)
{

}

void
update(SR_Canvas *canvas)
{

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
	init(&canvas);

event_loop:
	while (SDL_PollEvent(&ev))
		if (ev.type == SDL_QUIT)
			goto sdl_freesurf;

	/* Update code here */
	update(&canvas);

	if (SDL_BlitSurface(csurf, NULL, wsurf, NULL) < 0) {
		status = 6;
		goto sdl_freesurf;
	}

	if (SDL_UpdateWindowSurface(window) < 0) {
		status = 8;
		goto sdl_freesurf;
	}

	goto event_loop;

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
