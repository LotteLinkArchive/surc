#ifndef SURC_SCENE_H
#define SURC_SCENE_H
#include "../libs/surrender/src/surrender.h"

#include <stddef.h>
#include <stdint.h>

/*
 * Main scene struct
 */
struct SurcScene {
	uint16_t width;
	uint16_t height;
	uint8_t *map;

	/* Texture map */
	SR_Canvas *textures;
	size_t numTiles;
};

/*
 * Allocates the map of scene of width and height
 */
int surc_scene_new(struct SurcScene *const scene, const uint16_t width, const uint16_t height, size_t numTiles);

/*
 * Loads map into scene
 */
void surc_scene_load(struct SurcScene *const scene, const uint8_t *const map);

/*
 * Get map value
 */
uint8_t surc_scene_get_tile(struct SurcScene *const scene, const uint16_t x, const uint16_t y);

/*
 * Get texture for position in scene
 */
SR_Canvas surc_scene_get_texture(struct SurcScene *const scene, const uint16_t x, const uint16_t y);

/*
 * Map tile to id
 * Set tile to an empty SR_Canvas if you want no texture
 */
void surc_scene_set_texture(struct SurcScene *const scene, const size_t id, const SR_Canvas tile);

/*
 * Frees the map of scene
 */
void surc_scene_free(struct SurcScene *const scene);
#endif
