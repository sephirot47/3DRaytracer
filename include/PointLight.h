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
    
    float GetDiffuse(const Scene& scene, const Intersection &intersection) override;
    float GetSpecular(const Scene& scene, const Intersection &intersection) override;
    Ray GetLightRay(const Scene& scene, const Intersection &intersection) override;
};

#endif
