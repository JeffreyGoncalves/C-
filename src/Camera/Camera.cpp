#include "Camera.h"

Point3D const& Camera::getCameraPosition() const
{
	return this->cameraPosition;
}

void Camera::setCameraPosition(Point3D newCamPos)
{
	this->cameraPosition = newCamPos;
}
