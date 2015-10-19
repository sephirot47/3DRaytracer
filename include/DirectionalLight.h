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

    glm::vec3 LightIt(const Scene& scene, glm::vec3 pixelColor, const Intersection& intersection) override;
};

#endif
