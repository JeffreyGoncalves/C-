#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"

class Camera
{
	public : 
		//Constructeurs
		inline Camera() : cameraPosition(){}
		inline Camera(Point3D camPoint) : cameraPosition(camPoint){}
		inline Camera(double x_cam, double y_cam, double z_cam) : cameraPosition(x_cam, y_cam, z_cam){}
		///////////////
		//Getters
		Point3D const& getCameraPosition() const;
		///////////////
		//Setters
		void setCameraPosition(Point3D newCamPos);
		
	private :
		Point3D cameraPosition;
};

#endif
