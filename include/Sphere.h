#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive
{
public:
    double radius;
    
    Sphere();
    Sphere(const glm::dvec3& center, double radius);
    virtual ~Sphere();
    
    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) override;
};

#endif