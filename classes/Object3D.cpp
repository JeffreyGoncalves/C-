#include "Object3D.h"

Object3D::Object3D() : rgb(), reflexion(0.f) {}

Object3D::Object3D(Color C, float ref) : rgb(C), reflexion(ref) {}
