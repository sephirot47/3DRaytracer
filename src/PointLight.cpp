#include "../include/PointLight.h"
#include "../include/Scene.h"
#include <iostream>

using namespace std;


PointLight::PointLight()
{
  range = 5.0;
  intensity = 5.0;
}

PointLight::~PointLight() {}

sf::Color PointLight::LightIt(const Scene& scene, const sf::Color& color, const Intersection& intersection)
{

  Ray ray;
  ray.origin = this->center;
  ray.dir = glm::normalize(intersection.point - this->center);

  Intersection lightInter = intersection;
  scene.RayTrace(ray, lightInter);

  double epsilon = 0.0001;
  double shadow = 0.3;
  double d1 = glm::length(intersection.point - ray.origin);
  double d2 = glm::length(lightInter.point - ray.origin);
  bool isInShadow = abs(d2 - d1) > epsilon;
  if(!isInShadow)
  {
    glm::dvec3 lightDir = glm::normalize(intersection.point - this->center);
    double dist = glm::length(intersection.point - this->center);
    double attenuation = this->range / (dist == .0 ? .01f : dist);
    double dot = glm::dot(-lightDir, intersection.normal);
    double f = dot * attenuation * this->intensity;

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
