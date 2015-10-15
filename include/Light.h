#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "Intersection.h"
#include "Ray.h"
#include <SFML/Graphics.hpp>

class Scene;

class Light
{
public:
    glm::dvec3 center;
    sf::Color color;

    Light();
    virtual ~Light();

    virtual sf::Color LightIt(const Scene& scene, const sf::Color& color, const Intersection& intersection) = 0;
};

#endif
