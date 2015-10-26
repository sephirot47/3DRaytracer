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

Ray Ray::reflect(const Intersection &intersection) const
{
    Ray r; r.origin = intersection.point; r.dir = glm::normalize(glm::reflect(dir, intersection.normal)); return r;
}

Ray Ray::refract(const Intersection &intersection, bool fromVoid) const
{
    Ray r; r.origin = intersection.point; 
    double refr = fromVoid ? intersection.material->refraction : 1.0 / intersection.material->refraction;
    r.dir = glm::normalize(glm::refract(dir, intersection.normal, refr)); 
    return r;
}

Ray::~Ray() {}
