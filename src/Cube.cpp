#include "../include/Cube.h"

Cube::Cube()
{
    center = glm::vec3(0.0f);
    dimensions = glm::vec3(1.0f);
}

Cube::Cube(const glm::vec3& center, float size)
{
    this->center = center;
    this->dimensions = glm::vec3(size);
}

Cube::Cube(const glm::vec3& center, const glm::vec3 &dimensions)
{
    this->center = center;
    this->dimensions = dimensions;
}

Cube::~Cube() {}

/*
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
*/

bool inline Cube::InBox(const glm::vec3& Hit, const glm::vec3& B1, const glm::vec3& B2, const int Axis){}
bool inline Cube::Intersects( float fDst1, float fDst2, const glm::vec3& P1, const glm::vec3& P2,  glm::vec3 &Hit){}
int Cube::CheckIntersection(const glm::vec3& B1, const glm::vec3& B2, const glm::vec3& L1, const glm::vec3& L2, glm::vec3 &Hit){}
  
bool Cube::GetIntersection(const Ray &ray, Intersection &intersectionResult)
{
  //https://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm
  glm::vec3 lowestCorner = GetLowestCorner();
  glm::vec3 highestCorner = GetHighestCorner();
  float Tnear = -999999.0f, Tfar = 999999.9f;
  for(int i = 0; i < 3; ++i)
  {
    if (ray.dir[i] == 0)
    {
      if (ray.origin[i] < lowestCorner[i] or ray.origin[i] > highestCorner[i]) return false;
    }
    else
    {
      float T1 = (lowestCorner[i] - ray.origin[i]) / ray.dir[i];
      float T2 = (highestCorner[i] - ray.origin[i]) / ray.dir[i];
      if(T1 > T2) { float temp = T1; T1 = T2; T2 = temp; }
      if(T1 > Tnear) Tnear = T1; /* want largest Tnear */
      if(T2 < Tfar) Tfar = T2; /* want smallest Tfar */
      if(Tnear > Tfar || Tfar < 0) return false;
    }
  }
  
  //with intersection point Tnear and exit point Tfar.
  intersectionResult.point = ray.dir * Tnear;
  intersectionResult.normal = glm::vec3(0.0f, 1.0f, 0.0f);
  return true;
}