#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "glm/glm.hpp"

struct Intersection
{
    glm::vec3 point;   //The point of intersection
    glm::vec3 normal;  //The normal of the intersected primitive on the intersection point
};

#endif