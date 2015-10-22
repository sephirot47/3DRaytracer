#include "../include/Light.h"
#include "../include/Scene.h"
#include <iostream>
using namespace std;

Light::Light()
{
  intensity = 5.0;
  color = glm::vec3(255, 255, 255);
}

Light::~Light() {}

glm::vec3 Light::LightIt(const Scene& scene, glm::vec3 pixelColor, const Intersection& intersection)
{
  glm::vec3 color = glm::vec3(0.0f);
  glm::vec3 diffuse = glm::vec3(0.0f);
  glm::vec3 specular = glm::vec3(0.0f);

  Intersection lightInter = intersection;
  Ray ray = GetLightRay(scene, intersection);
  scene.RayTrace(ray, lightInter);
  
  double epsilon = 0.00001;
  double d1 = glm::length(intersection.point - ray.origin);
  double d2 = glm::length(lightInter.point - ray.origin);
  bool isInShadow = abs(d2 - d1) > epsilon;
  if(!isInShadow)
  {
    diffuse = intersection.material->diffuse * GetDiffuse(scene, intersection);
    specular = intersection.material->specular * GetSpecular(scene, intersection);
  }

  color = (diffuse + specular) * this->color;
  return pixelColor + color;
}