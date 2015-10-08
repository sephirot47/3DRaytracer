#include "glm/glm.hpp"

class Ray
{
public:
    glm::vec3 origin, dir;
    
    Ray(){}
    Ray(const glm::vec3 &origin,  const glm::vec3 &dir) { this->origin = origin; this->dir = dir; }
    virtual  ~Ray(){}
};