#ifndef SURC_CAMERA_H
#define SURC_CAMERA_H

/*
 * Vector2 struct
 * Didn't want to make another header lol
 */
struct SurcVect2f {
	float x;
	float y;
};

struct SurcVect2i {
	int x;
	int y;
};

/*
 * Basic camera that defines a position, rotation, camera plane, and height
 */
struct SurcCamera {
	struct SurcVect2f pos;
	struct SurcVect2f dir; /* direction vector */
	struct SurcVect2f cameraPlane;
	float height; /* in pixels */
};

#endif
