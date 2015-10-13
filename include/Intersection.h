#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "glm/glm.hpp"

struct Intersection
{
    glm::dvec3 point;   //The point of intersection
    glm::dvec3 normal;  //The normal of the intersected primitive on the intersection point
};

#endif
