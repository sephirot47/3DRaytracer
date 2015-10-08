#include "glm/glm.hpp"
#include "Ray.h"

class Primitive
{
protected:
    Primitive() { center = glm::vec3(0.0f); };
    virtual ~Primitive(){};
    
public:
    
    glm::vec3 center;

    virtual bool GetIntersection(const Ray &ray, glm::vec3 &intersectionPoint, glm::vec3 &normal) = 0;
};
