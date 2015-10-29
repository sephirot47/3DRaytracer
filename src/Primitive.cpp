#include "../include/Primitive.h"

Primitive::Primitive()
{
  center = glm::dvec3(0.0);
  material = new Material();
}

Primitive::~Primitive() {}
