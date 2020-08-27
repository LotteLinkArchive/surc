#ifndef SURC_SCENE_H
#define SURC_SCENE_H

#include <stdint.h>

/*
 * Main scene struct
 */
struct SurcScene {
	uint16_t width;
	uint16_t height;
	uint8_t *map;
};

/*
 * Allocates the map of scene of width and height
 */
int surc_scene_new(struct SurcScene *const scene, const uint16_t width, const uint16_t height);

/*
 * Loads map into scene
 */
void surc_scene_load(struct SurcScene *const scene, const uint8_t *const map);

/*
 * Get map value
 */
uint8_t surc_scene_get_tile(struct SurcScene *const scene, const uint16_t x, const uint16_t y);

/*
 * Frees the map of scene
 */
void surc_scene_free(struct SurcScene *const scene);
#endif
