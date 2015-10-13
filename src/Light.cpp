#include "../include/Light.h"
#include "../include/Scene.h"
#include <iostream>
using namespace std;

Light::Light()
{
  center = glm::vec3(0.0f);
  dir = glm::vec3(0.0f, 0.0f, 1.0f);
  range = 5.0f;
  intensity = 5.0f;
  color = sf::Color(255, 255, 255);

  type = LightType::Directional;
}

Light::~Light() {}

sf::Color Light::LightIt(const Scene& scene, const sf::Color& color, const Intersection& intersection)
{
  float f = 0.0f;

  Ray ray;
  if(this->type == LightType::Directional)
  {
    ray.origin = intersection.point - this->dir * 99999.9f;
    ray.dir = this->dir;
    //cout << "(" << ray.origin.x << ", " << ray.origin.y << ", " << ray.origin.z << ")"  << endl;
  }
  else if(this->type == LightType::Point)
  {
    ray.origin = this->center;
    ray.dir = glm::normalize(intersection.point - this->center);
  }

  Intersection lightInter = intersection;
  scene.RayTrace(ray, lightInter);

  float epsilon = 0.0001f;
  float d1 = glm::length(intersection.point - ray.origin);
  float d2 = glm::length(lightInter.point - ray.origin);
  bool isInShadow = abs(d2 - d1) > epsilon;
  if(!isInShadow)
  {
    if(this->type == LightType::Directional)
    {
      f = glm::dot(-this->dir, intersection.normal);
    }
    else if(this->type == LightType::Point)
    {
      glm::vec3 lightDir = glm::normalize(intersection.point - this->center);
      float dist = glm::length(intersection.point - this->center);
      float attenuation = this->range / (dist == .0f ? .01f : dist);
      float dot = glm::dot(-lightDir, intersection.normal);
      f = dot * attenuation * this->intensity;
    }

    unsigned char r = (unsigned char) glm::clamp(color.r * f, .0f, 255.0f);
    unsigned char g = (unsigned char) glm::clamp(color.g * f, .0f, 255.0f);
    unsigned char b = (unsigned char) glm::clamp(color.b * f, .0f, 255.0f);
    return sf::Color(r,g,b);
  }

  float shadow = 0.2f;
  unsigned char r = (unsigned char) glm::clamp(color.r * shadow, .0f, 255.0f);
  unsigned char g = (unsigned char) glm::clamp(color.g * shadow, .0f, 255.0f);
  unsigned char b = (unsigned char) glm::clamp(color.b * shadow, .0f, 255.0f);
  return sf::Color(r,g,b);
}
