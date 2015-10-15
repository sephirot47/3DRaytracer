#include "../include/Material.h"

using namespace std;


Material::Material()
{
  color = sf::Color(255, 0, 0);
  roughness = 1.0;
  shininess = 30.0;
}

Material::~Material() {}
