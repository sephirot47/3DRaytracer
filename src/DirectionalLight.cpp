#include "../include/DirectionalLight.h"
#include "../include/Scene.h"
#include <iostream>

using namespace std;


DirectionalLight::DirectionalLight()
{
  dir = glm::dvec3(0.0, 0.0, 1.0);
}

DirectionalLight::~DirectionalLight() {}

sf::Color DirectionalLight::LightIt(const Scene& scene, const Intersection& intersection)
{
  sf::Color color = intersection.material->color;
  Ray ray;
  ray.origin = intersection.point - this->dir * 9999.9;
  ray.dir = this->dir;

  Intersection lightInter = intersection;
  scene.RayTrace(ray, lightInter);

  double epsilon = 0.0001;
  double shadow = 0.3;
  double d1 = glm::length(intersection.point - ray.origin);
  double d2 = glm::length(lightInter.point - ray.origin);
  bool isInShadow = abs(d2 - d1) > epsilon;
  if(!isInShadow)
  {
    double f = glm::dot(-this->dir, intersection.normal);
    f*= intensity;
    f += shadow;
    f = glm::clamp(f, 0.0, 1.0);
    unsigned char r = (unsigned char) glm::clamp(color.r * f, .0, 255.0);
    unsigned char g = (unsigned char) glm::clamp(color.g * f, .0, 255.0);
    unsigned char b = (unsigned char) glm::clamp(color.b * f, .0, 255.0);
    return sf::Color(r,g,b);
  }

  unsigned char r = (unsigned char) glm::clamp(color.r * shadow, .0, 255.0);
  unsigned char g = (unsigned char) glm::clamp(color.g * shadow, .0, 255.0);
  unsigned char b = (unsigned char) glm::clamp(color.b * shadow, .0, 255.0);
  return sf::Color(r,g,b);
}
