#ifndef SURC_CAMERA_H
#define SURC_CAMERA_H

/*
 * Vector2 struct
 * Didn't want to make another header lol
 */
struct SurcVect2 {
	float x;
	float y;
};

/*
 * Basic camera that defines a player position
 * Only holds x and y as z is unneeded for raycasting calculations.
 */
struct SurcCamera {
	struct SurcVect2 pos;
	float yaw; /* rotation */
	float height; /* in pixels */
};

#endif
