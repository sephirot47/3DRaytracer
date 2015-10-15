#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "glm/glm.hpp"
#include "Intersection.h"
#include "Ray.h"

class Primitive
{
public:
    glm::dvec3 center;
    Material material;

    Primitive();
    virtual ~Primitive();

    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) = 0;
};

#endif
