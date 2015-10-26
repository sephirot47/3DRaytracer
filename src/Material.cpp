#include "../include/Material.h"

using namespace std;


Material::Material()
{
  ambient = glm::vec3(0.25f);
  diffuse = glm::vec3(0.5f);
  specular = glm::vec3(1.0f);

  roughness = 0.5;
  shininess = 30.0;
  alpha = 1.0;
  refraction = 2.5;
}

Material::~Material() {}
