#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "Intersection.h"
#include "Ray.h"
#include <SFML/Graphics.hpp>

class Scene;

enum LightType { Directional, Point };

class Light
{
public:
    LightType type;

    glm::dvec3 center;
    glm::dvec3 dir;

    double range, intensity;
    sf::Color color;

    Light();
    virtual ~Light();

    sf::Color LightIt(const Scene& scene, const sf::Color& color, const Intersection& intersection);
};

#endif
