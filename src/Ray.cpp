#include "../include/Ray.h"

Ray::Ray()
{
  origin = glm::vec3(0.0f);
  dir = glm::vec3(0.0f, 0.0f, 1.0f);
}

Ray::Ray(const glm::vec3 &origin,  const glm::vec3 &dir)
{
  this->origin = origin;
  this->dir = glm::normalize(dir);
}

Ray Ray::reflect(const Intersection &intersection)
{
  Ray r;
  r.origin = intersection.point;
  r.dir = this->dir - 2 * (glm::dot(this->dir,intersection.normal)) * intersection.normal;
  r.dir = glm::normalize(r.dir);
}

Ray::~Ray() {}
