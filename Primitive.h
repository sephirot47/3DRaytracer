#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "glm/glm.hpp"
#include "Ray.h"

class Primitive
{
protected:
    Primitive();
    virtual ~Primitive();
    
public:
    glm::vec3 center;

    virtual bool GetIntersection(const Ray &ray, glm::vec3 &intersectionPoint, glm::vec3 &normal) = 0;
};

#endif