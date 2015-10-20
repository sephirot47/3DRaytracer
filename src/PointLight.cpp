#include "../include/PointLight.h"
#include "../include/Scene.h"
#include <iostream>

using namespace std;


PointLight::PointLight()
    {
  center = glm::dvec3(0.0);
  range = 5.0;
}

PointLight::~PointLight() {}

glm::vec3 PointLight::LightIt(const Scene& scene, glm::vec3 pixelColor, const Intersection& intersection)
{
  glm::vec3 color = glm::vec3(0.0f);
  glm::vec3 diffuse, specular;
  diffuse = glm::vec3(0.0f);
  specular = glm::vec3(0.0f);

  Ray ray;
  ray.origin = this->center;
  ray.dir = glm::normalize(intersection.point - this->center);

  Intersection lightInter = intersection;
  scene.RayTrace(ray, lightInter);

  double epsilon = 0.0001;
  double d1 = glm::length(intersection.point - ray.origin);
  double d2 = glm::length(lightInter.point - ray.origin);
  bool isInShadow = abs(d2 - d1) > epsilon;
  if(!isInShadow)
  {
    //Diffuse
    glm::dvec3 lightDir = glm::normalize(intersection.point - this->center);
    double dist = glm::length(intersection.point - this->center);
    double attenuation = this->range / (dist == .0 ? .01f : dist);
    double dot = glm::dot(-lightDir, intersection.normal);
    double f = dot * attenuation * this->intensity;
    f = glm::clamp(f, 0.0, 1.0);
    diffuse = intersection.material->diffuse * float(f);

    //Specular
    glm::dvec3 reflectDir = glm::normalize(ray.reflect(intersection).dir);
    glm::dvec3 camToPointDir = glm::normalize(glm::dvec3(0) - intersection.point);
    dot = glm::dot(reflectDir, camToPointDir);
    dot = glm::pow(dot, intersection.material->shininess);
    f = dot * attenuation * this->intensity;
    f = glm::clamp(f, 0.0, 1.0);
    specular = intersection.material->specular * float(f);
  }

  color = (diffuse + specular) * this->color;
  return pixelColor + color;
}
