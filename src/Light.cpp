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
  glm::vec3 colorSubstraction = glm::vec3(0.0f);
  glm::vec3 diffuse = glm::vec3(0.0f); 
  glm::vec3 specular = glm::vec3(0.0f);

  Ray lightRay = GetLightRay(intersection);
  Intersection lightInter;
  lightInter.point = lightRay.origin;

  glm::dvec3 lightRayOrigin = lightRay.origin;
  double epsilon = 0.00001;
  double d1 = glm::length(intersection.point - lightRayOrigin);
  double d2;
  bool arrivedToDest;
  do
  {
    lightRay.origin = lightInter.point + lightRay.dir * epsilon;
    scene.RayTrace(lightRay, lightInter);
    
    d2 = glm::length(lightInter.point - lightRayOrigin);
    arrivedToDest = abs(d2 - d1) <= epsilon || (lightInter.material->alpha >= 1.0);
    if(!arrivedToDest)
    {
        glm::vec3 colorSubs = glm::vec3(1.0f) - lightInter.material->diffuse;
        colorSubs *= lightInter.material->alpha;
        
        colorSubstraction += colorSubs;   
    }
  }
  while(!arrivedToDest);
  
  if( abs(d2 - d1) <= epsilon)
  {
    diffuse = lightInter.material->diffuse * GetDiffuse(scene, lightInter, lightRay);
    specular = lightInter.material->specular * GetSpecular(scene, lightInter, lightRay);
  }
  
  glm::vec3 finalApportation = (diffuse + specular) * (this->color - colorSubstraction);
  finalApportation.x = glm::clamp(0.0f, 1.0f, finalApportation.x);
  finalApportation.y = glm::clamp(0.0f, 1.0f, finalApportation.y);
  finalApportation.z = glm::clamp(0.0f, 1.0f, finalApportation.z);
  
  return pixelColor + finalApportation; 
}