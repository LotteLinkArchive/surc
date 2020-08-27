#include <stdlib.h>
#include <string.h>

#include "scene.h"

int
surc_scene_new(struct SurcScene *const scene, uint16_t width, uint16_t height)
{
	scene->width = width;
	scene->height = height;

	return (scene->map = calloc(width*height, sizeof(uint8_t))) != NULL;
}

void
surc_scene_load(struct SurcScene *const scene, const uint8_t *const map)
{
	memcpy(scene->map, map, scene->width*scene->height);
}

uint8_t surc_scene_get_tile(struct SurcScene *const scene, const uint16_t x, const uint16_t y)
{
	return scene->map[y*scene->width + x];
}

void
surc_scene_free(struct SurcScene *const scene)
{
	free(scene->map);
}
