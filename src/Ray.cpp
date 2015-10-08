#include "../include/Ray.h"

Ray::Ray()
{
  origin = glm::vec3(0.0f);
  dir = glm::vec3(0.0f);
}

Ray::Ray(const glm::vec3 &origin,  const glm::vec3 &dir) 
{
  this->origin = origin; 
  this->dir = dir; 
}

Ray::~Ray() {}
