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

float PointLight::GetDiffuse(const Scene& scene, const Intersection &intersection)
{
    double f = 0.0;
    glm::dvec3 lightDir = glm::normalize(intersection.point - this->center);
    double dist = glm::length(intersection.point - this->center);
    double attenuation = this->range / (dist == .0 ? .01f : dist);
    double dot = glm::dot(-lightDir, intersection.normal);
    f = dot * attenuation * this->intensity;
    f = glm::clamp(f, 0.0, 1.0);
    return float(f);
}

float PointLight::GetSpecular(const Scene& scene, const Intersection &intersection)
{
    double epsilon =  0.00001;
    double f = 0.0;
    Ray ray = GetLightRay(scene, intersection);
    glm::dvec3 reflectDir = glm::normalize(ray.reflect(intersection).dir);
    glm::dvec3 camToPointDir = glm::normalize(glm::dvec3(0) - intersection.point);
    double dot = glm::dot(reflectDir, camToPointDir);
    if(dot > epsilon)
    {
        double dist = glm::length(intersection.point - this->center);
        double attenuation = this->range / (dist == .0 ? .01f : dist);
        dot = glm::pow(dot, intersection.material->shininess);
        f = dot * attenuation * this->intensity;
        f = glm::clamp(f, 0.0, 1.0);
    }
    return float(f);
}


Ray PointLight::GetLightRay(const Scene& scene, const Intersection &intersection)
{
  Ray ray;
  ray.origin = this->center;
  ray.dir = glm::normalize(intersection.point - this->center);
}