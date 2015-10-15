#include "../include/Cube.h"

Cube::Cube()
{
    center = glm::dvec3(0.0);
    dimensions = glm::dvec3(1.0);
}

Cube::Cube(const glm::dvec3& center, double size)
{
    this->center = center;
    this->dimensions = glm::dvec3(size);
}

Cube::Cube(const glm::dvec3& center, const glm::dvec3 &dimensions)
{
    this->center = center;
    this->dimensions = dimensions;
}

Cube::~Cube() {}

bool Cube::GetIntersection(const Ray &ray, Intersection &intersectionResult)
{
  //https://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm
  glm::dvec3 lowestCorner = GetLowestCorner();
  glm::dvec3 highestCorner = GetHighestCorner();
  double Tnear = -99999.0, Tfar = 99999.9;
  for(int i = 0; i < 3; ++i)
  {
    if (ray.dir[i] == 0)
    {
      if (ray.origin[i] < lowestCorner[i] or ray.origin[i] > highestCorner[i]) return false;
    }
    else
    {
      double T1 = (lowestCorner[i] - ray.origin[i]) / ray.dir[i];
      double T2 = (highestCorner[i] - ray.origin[i]) / ray.dir[i];
      if(T1 > T2) { double temp = T1; T1 = T2; T2 = temp; }
      if(T1 > Tnear) Tnear = T1; /* want largest Tnear */
      if(T2 < Tfar) Tfar = T2; /* want smallest Tfar */

      if(Tnear > Tfar || Tfar < 0) return false;
    }
  }

  //with intersection point Tnear and exit point Tfar.
  intersectionResult.point = ray.origin + ray.dir * Tnear;

  glm::dvec3 p = intersectionResult.point;
  double epsilon = 0.001;
  if      (abs(p.x - lowestCorner.x) < epsilon) intersectionResult.normal = glm::dvec3(-1.0, 0.0, 0.0);
  else if (abs(p.x - highestCorner.x) < epsilon) intersectionResult.normal = glm::dvec3(1.0,  0.0, 0.0);
  else if (abs(p.y - lowestCorner.y) < epsilon) intersectionResult.normal = glm::dvec3(0.0, -1.0, 0.0);
  else if (abs(p.y - highestCorner.y) < epsilon) intersectionResult.normal = glm::dvec3(0.0,  1.0, 0.0);
  else if (abs(p.z - lowestCorner.z) < epsilon) intersectionResult.normal = glm::dvec3(0.0, 0.0, -1.0);
  else intersectionResult.normal = glm::dvec3(0.0,  0.0, 1.0);
  intersectionResult.material = &material;
  return true;
}
