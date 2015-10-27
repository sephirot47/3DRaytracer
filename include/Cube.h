#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

using namespace std;

class Cube : public Primitive
{
private:

    bool inline Intersects(double fDst1, double fDst2, const glm::dvec3& P1, const glm::dvec3& P2, glm::dvec3 &Hit);
    bool inline InBox(const glm::dvec3& Hit, const glm::dvec3& B1, const glm::dvec3& B2, const int Axis);
    int CheckIntersection(const glm::dvec3& B1, const glm::dvec3& B2, const glm::dvec3& L1, const glm::dvec3& L2, glm::dvec3 &Hit);

public:
    
    glm::dvec3 dimensions;
    
    Cube();
    Cube(const glm::dvec3& center, double size);
    Cube(const glm::dvec3& center, const glm::dvec3 &dimensions);
    virtual ~Cube();

    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) override;

    glm::dvec3 GetLowestCorner() { return center - dimensions; }
    glm::dvec3 GetHighestCorner() { return center + dimensions; }
};

#endif
