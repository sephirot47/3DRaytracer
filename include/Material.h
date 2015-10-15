#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>

class Material
{
public:
    Material();
    virtual ~Material();

    sf::Color color;

    double shininess;
    double roughness;
};

#endif
