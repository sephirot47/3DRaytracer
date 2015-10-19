#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "glm/glm.hpp"
#include "Intersection.h"
#include "Light.h"
#include "Ray.h"
#include <SFML/Graphics.hpp>

class Scene;

class PointLight : public Light
{
public:
    glm::dvec3 center;
    double range;

    PointLight();
    virtual ~PointLight();

    glm::vec3 LightIt(const Scene& scene, glm::vec3 pixelColor, const Intersection& intersection) override;
};

#endif
