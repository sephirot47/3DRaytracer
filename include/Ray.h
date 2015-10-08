#ifndef RAY_H
#define RAY_H

#include "glm/glm.hpp"

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