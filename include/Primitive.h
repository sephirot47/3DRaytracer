#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "glm/glm.hpp"
#include "Ray.h"

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();
    
    glm::vec3 center;

    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) = 0;
};

#endif