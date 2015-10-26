#ifndef RAY_H
#define RAY_H

#include "glm/glm.hpp"
#include "Intersection.h"

class Ray
{
public:
    glm::dvec3 origin;
    glm::dvec3 dir;

    Ray();
    Ray(const glm::dvec3 &origin,  const glm::dvec3 &dir);
    virtual ~Ray();

    Ray reflect(const Intersection &intersection) const;
    Ray refract(const Intersection &intersection, bool fromVoid) const;
};

#endif
