#include "Primitive.h"

class Sphere : public Primitive
{
public:
    float radius;
    
    Sphere(){}
    virtual ~Sphere(){}
    
    virtual bool GetIntersection(const Ray &ray, glm::vec3 &intersectionPoint, glm::vec3 &normal) override;
};