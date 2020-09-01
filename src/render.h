#ifndef SURC_RENDER_H
#define SURC_RENDER_H
#include "../libs/surrender/src/surrender.h"

#include "camera.h"
#include "scene.h"

/* Macros for overlay settings */
#define OVERLAY_TILE_SIZE 16
#define CAMERA_SIZE 4
#define DIR_VECTOR_LEN 10

/* Renders a raycast frame */
void
surc_render_frame(SR_Canvas *canvas,
                  struct SurcScene *const scene,
                  struct SurcCamera *const camera);

/* Renders the overlay */
void
surc_render_overlay(SR_Canvas *canvas,
                    struct SurcScene *const scene,
                    struct SurcCamera *const camera);
#endif
