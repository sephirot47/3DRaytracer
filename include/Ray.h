#ifndef RAY_H
#define RAY_H

#include "glm/glm.hpp"

struct Intersection
{
    glm::vec3 point;   //The point of intersection
    glm::vec3 normal;  //The normal of the intersected primitive on the intersection point
};

class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 dir;
    
    Ray();
    Ray(const glm::vec3 &origin,  const glm::vec3 &dir);
    virtual ~Ray();
};

#endif