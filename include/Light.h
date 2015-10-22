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
    float intensity;
    glm::vec3 color;

    Light();
    virtual ~Light();

    glm::vec3 LightIt(const Scene& scene, glm::vec3 pixelColor, const Intersection& intersection);
    virtual float GetDiffuse(const Scene& scene, const Intersection &intersection) = 0;
    virtual float GetSpecular(const Scene& scene, const Intersection &intersection) = 0;
    virtual Ray GetLightRay(const Scene& scene, const Intersection &intersection) = 0;
};

#endif
