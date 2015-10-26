#include "../include/Sphere.h"
#include <iostream>

Sphere::Sphere()
{
  radius = 1.0;
}

Sphere::Sphere(const glm::dvec3& center, double radius)
{
  this->center = center;
  this->radius = radius;
}

Sphere::~Sphere() {}

bool Sphere::GetIntersection(const Ray &ray, Intersection &intersectionResult)
{
    glm::dvec3 rayFarPoint = ray.origin + ray.dir * 99999.9;

    double cx = center.x, cy = center.y, cz = center.z;
    double px = ray.origin.x, py = ray.origin.y, pz = ray.origin.z;

    double vx = rayFarPoint.x - px;
    double vy = rayFarPoint.y - py;
    double vz = rayFarPoint.z - pz;

    double A = vx * vx + vy * vy + vz * vz;
    double B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
    double C = px * px - 2.0 * px * cx + cx * cx + py * py - 2.0 * py * cy + cy * cy +
                pz * pz - 2.0 * pz * cz + cz * cz - radius * radius;

    // discriminant
    double D = B * B - 4.0 * A * C;

    if ( D < 0.0 ) return false;    

    double t1 = ( -B - sqrt( D ) ) / ( 2.0 * A );

    glm::dvec3 solution1 = glm::dvec3( ray.origin.x * ( 1.0 - t1 ) + t1 * rayFarPoint.x,
                                     ray.origin.y * ( 1.0 - t1 ) + t1 * rayFarPoint.y,
                                     ray.origin.z * ( 1.0 - t1 ) + t1 * rayFarPoint.z );

    glm::dvec3 solutionDir = glm::normalize(solution1 - ray.origin);
    if(glm::dot(ray.dir, solutionDir) < 0.9) return false;

    double epsilon = 0.1;
    if ( abs(D) < epsilon )
    {
        intersectionResult.point = solution1;
        intersectionResult.normal = glm::normalize(intersectionResult.point - center);
        intersectionResult.material = &material;
        return true;
    }

    double t2 = ( -B + sqrt( D ) ) / ( 2.0 * A );
    glm::dvec3 solution2 = glm::dvec3( ray.origin.x * ( 1.0 - t2 ) + t2 * rayFarPoint.x,
                                     ray.origin.y * ( 1.0 - t2 ) + t2 * rayFarPoint.y,
                                     ray.origin.z * ( 1.0 - t2 ) + t2 * rayFarPoint.z );

    solutionDir = glm::normalize(solution2 - ray.origin);
    if(glm::dot(ray.dir, solutionDir) < 0.9) return false;

    if (glm::length(ray.origin - solution1) < glm::length(ray.origin - solution2)) intersectionResult.point = solution1;
    else intersectionResult.point = solution2;

    intersectionResult.normal = glm::normalize(intersectionResult.point - center);
    intersectionResult.material = &material;
    return true;
}
