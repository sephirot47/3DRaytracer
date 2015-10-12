#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

using namespace std;

class Cube : public Primitive
{
private:
    
    bool inline Intersects(float fDst1, float fDst2, const glm::vec3& P1, const glm::vec3& P2, glm::vec3 &Hit);
    bool inline InBox(const glm::vec3& Hit, const glm::vec3& B1, const glm::vec3& B2, const int Axis);
    int CheckIntersection(const glm::vec3& B1, const glm::vec3& B2, const glm::vec3& L1, const glm::vec3& L2, glm::vec3 &Hit);
    glm::vec3 dimensions;
    
public:
    
    Cube();
    Cube(const glm::vec3& center, float size);
    Cube(const glm::vec3& center, const glm::vec3 &dimensions);
    virtual ~Cube();

    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) override;
    
    glm::vec3 GetLowestCorner() { return center - dimensions; }
    glm::vec3 GetHighestCorner() { return center + dimensions; }
};

#endif