#ifndef MOUSERAY_H
#define MOUSERAY_H

#include "math/Ray.h"
#include "MMath.h"
#include "Camera.h"

//! MouseRay class
/*! This class is used for taking in our mouse position on screen and converting it 
into world coordinates */
class MouseRay
{
private:

	//! Vector3 Current Ray
	/*! Is the direction on the current ray */
	Ray* ray = new Ray();

	//! Vector2 Local Mouse Position
	/*! Where the mouse is in local/screen coordinates */
	MATH::Vec2 localMousePos;

	//! Vec2 Function GetDeviceCoords
	/*! Converts the local Mouse Position to normal Coordinates */
	MATH::Vec2 GetDeviceCoords(int x_, int y_);

	//! Vec4 Function GetEyeCoords
	/*! Converts clipping Coordinates to eye Coordinates */
	MATH::Vec4 GetEyeCoords(MATH::Vec4 clipCoords);

	//! Vec3 Function GetWorldCoords
	/*! Converts eye Coordinates to world Coordinates */
	MATH::Vec3 GetWorldCoords(MATH::Vec4 eyeCoords);


public:

	//! MouseRay Constructor
	MouseRay();

	//! MouseRay Destructor
	~MouseRay();

	//! Vector3 Inverse Ray
	/*! Is the inverse of the currentRay */
	MATH::Vec3 invDir;

	

	//! Calculate Mouse Ray Function
	/*! Does the final calculation and then updates the currentRay */
	void CalaculateMouseRay();

	//! Get Current Ray Getter
	/*! Returns the current ray */
	const Ray* GetCurrentRay() { return ray; }

	//! Handle Events Function
	/*! Used for getting the mouse position in local/screen space */
	void HandleEvents(const SDL_Event& event);
};

#endif