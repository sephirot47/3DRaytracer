#include "../include/Ray.h"

Ray::Ray()
{
  origin = glm::dvec3(0.0);
  dir = glm::dvec3(0.0, 0.0, 1.0);
}

Ray::Ray(const glm::dvec3 &origin,  const glm::dvec3 &dir)
{
  this->origin = origin;
  this->dir = glm::normalize(dir);
}

Ray Ray::reflect(const Intersection &intersection)
{
  Ray r;
  r.origin = intersection.point;
  r.dir = glm::normalize(this->dir) - 2 * (glm::dot(this->dir, glm::normalize(intersection.normal))) * glm::normalize(intersection.normal);
  r.dir = glm::normalize(r.dir);
}

Ray::~Ray() {}
