#include <stdlib.h>
#include <string.h>

#include "scene.h"

int
surc_scene_new(struct SurcScene *const scene, uint16_t width, uint16_t height, size_t numTiles)
{
	scene->width = width;
	scene->height = height;

	if (!(scene->map = calloc(width*height, sizeof(uint8_t)))) {
		return 0;
	}

	if (!(scene->textures = calloc(numTiles, sizeof(SR_Canvas)))) {
		free(scene->map);
		return 0;
	}

	return 1;
}

void
surc_scene_load(struct SurcScene *const scene, const uint8_t *const map)
{
	memcpy(scene->map, map, scene->width*scene->height);
}

uint8_t
surc_scene_get_tile(struct SurcScene *const scene, const uint16_t x, const uint16_t y)
{
	return scene->map[y*scene->width + x];
}

SR_Canvas
surc_scene_get_texture(struct SurcScene *const scene, const uint16_t x, const uint16_t y)
{
	return scene->textures[surc_scene_get_tile(scene, x, y)];
}

void
surc_scene_set_texture(struct SurcScene *const scene, const size_t id, const SR_Canvas tile)
{
	scene->textures[id] = tile;
}

void
surc_scene_free(struct SurcScene *const scene)
{
	free(scene->textures);
	free(scene->map);
}
