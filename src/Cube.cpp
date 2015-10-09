#include "../include/Cube.h"

Cube::Cube()
{
    center = glm::vec3(0.0f);
    lowestCorner = glm::vec3(-1.0f);
    highestCorner = glm::vec3(1.0f);
}

Cube::Cube(const glm::vec3& center, float size)
{
    this->center = center;
    lowestCorner  = center - glm::vec3(size);
    highestCorner = center + glm::vec3(size);
}
    
Cube::Cube(const glm::vec3& center, glm::vec3 &dimensions)
{
    this->center = center;
    lowestCorner  = center -  glm::vec3(dimensions.x, dimensions.y, dimensions.z);
    highestCorner = center +  glm::vec3(dimensions.x, dimensions.y, dimensions.z);
}

Cube::~Cube() {}
    
bool Cube::GetIntersection(const Ray &ray, Intersection &intersectionResult)
{
    glm::vec3 l1 = ray.origin;
    glm::vec3 l2 = ray.origin + ray.dir * 99999.9f;
    return CheckIntersection(lowestCorner, highestCorner, l1, l2, intersectionResult.point) && false;
}

int Cube::CheckIntersection(const glm::vec3& B1, const glm::vec3& B2, const glm::vec3& L1, const glm::vec3& L2, glm::vec3 &Hit)
{
    if (L2.x < B1.x && L1.x < B1.x) return false;
    if (L2.x > B2.x && L1.x > B2.x) return false;
    if (L2.y < B1.y && L1.y < B1.y) return false;
    if (L2.y > B2.y && L1.y > B2.y) return false;
    if (L2.z < B1.z && L1.z < B1.z) return false;
    if (L2.z > B2.z && L1.z > B2.z) return false;
    if (L1.x > B1.x && L1.x < B2.x &&
        L1.y > B1.y && L1.y < B2.y &&
        L1.z > B1.z && L1.z < B2.z) 
        {
            Hit = L1; 
            return true;
        }
    
    return ( (Intersects( L1.x-B1.x, L2.x-B1.x, L1, L2, Hit) && InBox( Hit, B1, B2, 1 ))
        ||   (Intersects( L1.y-B1.y, L2.y-B1.y, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
        ||   (Intersects( L1.z-B1.z, L2.z-B1.z, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )) 
        ||   (Intersects( L1.x-B2.x, L2.x-B2.x, L1, L2, Hit) && InBox( Hit, B1, B2, 1 )) 
        ||   (Intersects( L1.y-B2.y, L2.y-B2.y, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
        ||   (Intersects( L1.z-B2.z, L2.z-B2.z, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )));
}

bool inline Cube::Intersects( float fDst1, float fDst2, const glm::vec3& P1, const glm::vec3& P2,  glm::vec3 &Hit) 
{
    if ( (fDst1 * fDst2) >= 0.0f) return false;
    if ( fDst1 == fDst2) return false; 
    Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
    return true;
}

bool inline Cube::InBox(const glm::vec3& Hit, const glm::vec3& B1, const glm::vec3& B2, const int Axis) 
{
    if ( Axis==1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return true;
    if ( Axis==2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return true;
    if ( Axis==3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return true;
    return true;
}
