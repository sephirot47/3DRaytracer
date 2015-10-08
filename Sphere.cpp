#include "Sphere.h"

bool Sphere::GetIntersection(const Ray &ray, glm::vec3 &intersectionPoint, glm::vec3 &normal)
{
    glm::vec3 rayFarPoint = ray.origin + ray.dir * 99999.9f;
    
    float cx = center.x, cy = center.y, cz = center.z;
    float px = ray.origin.x, py = ray.origin.y, pz = ray.origin.z;

    float vx = rayFarPoint.x - px;
    float vy = rayFarPoint.y - py;
    float vz = rayFarPoint.z - pz;

    float A = vx * vx + vy * vy + vz * vz;
    float B = 2.0f * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
    float C = px * px - 2.0f * px * cx + cx * cx + py * py - 2.0f * py * cy + cy * cy +
                pz * pz - 2.0f * pz * cz + cz * cz - radius * radius;

    // discriminant
    float D = B * B - 4.0f * A * C;

    if ( D < 0.0f )
    {
        intersectionPoint = glm::vec3(0.0f);
        normal = glm::normalize(intersectionPoint - center);
        return false;
    }

    float t1 = ( -B - sqrt( D ) ) / ( 2.0f * A );

    glm::vec3 solution1 = glm::vec3( ray.origin.x * ( 1.0f - t1 ) + t1 * rayFarPoint.x,
                                     ray.origin.y * ( 1.0f - t1 ) + t1 * rayFarPoint.y,
                                     ray.origin.z * ( 1.0f - t1 ) + t1 * rayFarPoint.z );
    
    if ( D == 0.0f ) 
    { 
        intersectionPoint = solution1;
        normal = glm::normalize(intersectionPoint - center);
        return true;
    }
    
    float t2 = ( -B + sqrt( D ) ) / ( 2.0f * A );
    glm::vec3 solution2 = glm::vec3( ray.origin.x * ( 1.0f - t2 ) + t2 * rayFarPoint.x,
                                     ray.origin.y * ( 1.0f - t2 ) + t2 * rayFarPoint.y,
                                     ray.origin.z * ( 1.0f - t2 ) + t2 * rayFarPoint.z );

    if (glm::length(ray.origin - solution1) < glm::length(ray.origin - solution2)) intersectionPoint = solution1; 
    else intersectionPoint = solution2;
    
    
    normal = glm::normalize(intersectionPoint - center);
    return true;
}
 