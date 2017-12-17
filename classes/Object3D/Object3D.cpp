#include "Object3D.h"

Object3D::Object3D() : rgb(), reflexion(0.f) {}

Object3D::Object3D(Color C, float ref) : rgb(C), reflexion(ref) {}

Object3D::~Object3D() {}

Color const& Object3D::getObjectColor()
{
	return this->rgb;
}

ray3D Object3D::calcReflexionRay(Point3D reflectedRayOrigin, ray3D r)
{
	vec3D v_incident(r.getRayDirection()),
		  normale(this->calcNormToPoint(reflectedRayOrigin));
		  
	vec3D reflectedVec3D = v_incident - normale.times(2*(v_incident.dot(normale)));
	
	return ray3D(reflectedRayOrigin, reflectedVec3D);
}
