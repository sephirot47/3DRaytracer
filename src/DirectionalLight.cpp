#include "../include/DirectionalLight.h"
#include "../include/Scene.h"
#include <iostream>

using namespace std;

DirectionalLight::DirectionalLight()
{
  dir = glm::dvec3(0.0, 0.0, 1.0);
}

DirectionalLight::~DirectionalLight() {}

float DirectionalLight::GetDiffuse(const Scene& scene, const Intersection &intersection)
{
    double dot = glm::dot(-this->dir, glm::normalize(intersection.normal));
    double f = dot * intensity;
    f = glm::clamp(f, 0.0, 1.0);
    return float(f);
}

float DirectionalLight::GetSpecular(const Scene& scene, const Intersection &intersection)
{
    Ray ray = GetLightRay(scene, intersection);
    glm::dvec3 reflectDir = glm::normalize(ray.reflect(intersection).dir);
    glm::dvec3 pointToCamDir = glm::normalize(glm::dvec3(0) - intersection.point);
    double dot = glm::dot(reflectDir, pointToCamDir);
    dot = glm::pow(dot, intersection.material->shininess);
    double f = dot * this->intensity;
    f = glm::clamp(f, 0.0, 1.0);
    return float(f);
}

Ray DirectionalLight::GetLightRay(const Scene& scene, const Intersection &intersection)
{
  Ray ray;
  ray.origin = intersection.point - this->dir * 9999.9;
  ray.dir = this->dir;
}