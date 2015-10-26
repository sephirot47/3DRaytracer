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

float PointLight::GetDiffuse(const Scene& scene, const Intersection& intersection, const Ray &ray)
{
  //Diffuse
  glm::dvec3 lightDir = glm::normalize(intersection.point - this->center);
  double dist = glm::length(intersection.point - this->center);
  double attenuation = this->range / (dist == .0 ? .01f : dist);
  double dot = glm::dot(-lightDir, intersection.normal);
  double f = dot * attenuation * this->intensity;
  f = glm::clamp(f, 0.0, 1.0);
  return float(f);
}

float PointLight::GetSpecular(const Scene& scene, const Intersection& intersection, const Ray &ray)
{
  //Specular
  double dist = glm::length(intersection.point - this->center);
  double attenuation = this->range / (dist == .0 ? .01f : dist);
  glm::dvec3 reflectDir = glm::normalize(ray.reflect(intersection).dir);
  glm::dvec3 camToPointDir = glm::normalize(glm::dvec3(0) - intersection.point);
  double dot = glm::dot(reflectDir, camToPointDir);
  double f = 0.0;
  double epsilon = 0.0001;
  if(dot > epsilon)
  {
      dot = glm::pow(dot, intersection.material->shininess);
      f = dot * attenuation * this->intensity;
      f = glm::clamp(f, 0.0, 1.0);
  }
  return float(f);
}

Ray PointLight::GetLightRay(const Intersection& intersection)
{
  Ray ray;
  ray.origin = this->center;
  ray.dir = glm::normalize(intersection.point - this->center);
  return ray;
}