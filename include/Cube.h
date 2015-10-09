#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

class Cube : public Primitive
{
private:
    
    bool inline Intersects(float fDst1, float fDst2, const glm::vec3& P1, const glm::vec3& P2, glm::vec3 &Hit);
    bool inline InBox(const glm::vec3& Hit, const glm::vec3& B1, const glm::vec3& B2, const int Axis);
    int CheckIntersection(const glm::vec3& B1, const glm::vec3& B2, const glm::vec3& L1, const glm::vec3& L2, glm::vec3 &Hit);
    
public:
    glm::vec3 lowestCorner;  //the smallest values of X, Y, Z
    glm::vec3 highestCorner; //the largest values of X, Y, Z 
    
    Cube();
    Cube(const glm::vec3& center, float size);
    Cube(const glm::vec3& center, glm::vec3 &dimensions);
    virtual ~Cube();

    virtual bool GetIntersection(const Ray &ray, Intersection &intersectionResult) override;
};

#endif