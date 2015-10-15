#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "glm/glm.hpp"
#include "Material.h"

struct Intersection
{
    glm::dvec3 point;   //The point of intersection
    glm::dvec3 normal;  //The normal of the intersected primitive on the intersection point
    Material *material;
};

#endif
