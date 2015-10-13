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

  glm::vec3 p = intersectionResult.point;
  float epsilon = 0.001;
  if      (abs(p.x - lowestCorner.x) < epsilon) intersectionResult.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
  else if (abs(p.x - highestCorner.x) < epsilon) intersectionResult.normal = glm::vec3(1.0f,  0.0f, 0.0f);
  else if (abs(p.y - lowestCorner.y) < epsilon) intersectionResult.normal = glm::vec3(0.0f, -1.0f, 0.0f);
  else if (abs(p.y - highestCorner.y) < epsilon) intersectionResult.normal = glm::vec3(0.0f,  1.0f, 0.0f);
  else if (abs(p.z - lowestCorner.z) < epsilon) intersectionResult.normal = glm::vec3(0.0f, 0.0f, -1.0f);
  else intersectionResult.normal = glm::vec3(0.0f,  0.0f, 1.0f);
  return true;
}
