#include "Object3D.h"

Object3D::Object3D() : rgb(), reflexion(0.f), alpha(0.f) {}

Object3D::Object3D(Color C, float ref, float a) : rgb(C), reflexion(ref), alpha(a){}

Object3D::~Object3D() {}

Color const& Object3D::getObjectColor()
{
	return this->rgb;
}

float const& Object3D::getObjectReflexionFactor()
{
	return this->reflexion;
}

float const& Object3D::getObjectAlpha()
{
	return this->alpha;
}

ray3D Object3D::calcReflexionRay(Point3D reflectedRayOrigin, ray3D r)
{
	vec3D v_incident(r.getRayDirection()),
		  normale(this->calcNormToPoint(reflectedRayOrigin));
		  
	vec3D reflectedVec3D = v_incident - normale.times(2*(normale.dot(v_incident)));
	//Pourquoi ca marche ??? Ca devrait etre un echec
	
	return ray3D(reflectedRayOrigin, reflectedVec3D);
}
