#include "Object3D.h"

Object3D::Object3D() : rgb(), reflexion(0.f), alpha(0.f), refraction(1.0f) {}

Object3D::Object3D(Color C, float ref, float a, float refrac) : rgb(C)
{
	//Reflexion
	if(ref < 0)reflexion = 0.f;
	else if(ref > 1)reflexion = 1.f;
	else reflexion = ref;
	
	//Alpha
	if(a < 0)alpha = 0.f;
	else if(a > 1)alpha = 1.f;
	else alpha = a;
	
	//Refraction
	if(refrac < 1)refraction = 1.f;
	else refraction = refrac;
}

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

/*ray3D Object3D::calcRefractedToPoint(Point3D p)
{
	
}*/
