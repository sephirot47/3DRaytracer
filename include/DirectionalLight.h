#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "glm/glm.hpp"
#include "Intersection.h"
#include "Light.h"
#include "Ray.h"
#include <SFML/Graphics.hpp>

class Scene;

class DirectionalLight : public Light
{
public:
    glm::dvec3 dir;

    DirectionalLight();
    virtual ~DirectionalLight();

    sf::Color LightIt(const Scene& scene, sf::Color pixelColor, const Intersection& intersection) override;
};

#endif
