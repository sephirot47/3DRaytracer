#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive
{
public:
    float radius;
    
    Sphere();
    Sphere(const glm::vec3& center, float radius);
    virtual ~Sphere();
    
    virtual bool GetIntersection(const Ray &ray, glm::vec3 &intersectionPoint, glm::vec3 &normal) override;
};

#endif