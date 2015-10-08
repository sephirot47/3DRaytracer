#include <iostream>
#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

//#define BIG
#ifdef BIG
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;
#endif

#ifndef BIG
const int WINDOW_WIDTH = 450;
const int WINDOW_HEIGHT = 350;
#endif

const float aspectRatio = float(WINDOW_WIDTH) / WINDOW_HEIGHT;

const int FOV = 60; //degrees
const float R_FOV = FOV * 3.1415926535f/180.0f;
const float ZNEAR = 5.0f;

const float vpWidth = ZNEAR * tan(R_FOV/2);
const float vpHeight = vpWidth / aspectRatio;

float timeCount = 0.0f;

bool intersectsSphere(glm::vec3 sphereCenter, float sphereRadius, glm::vec3 rayd, 
                      glm::vec3 &closestIntersection, glm::vec3 &normal)
{
    glm::vec3 rayOrigin = glm::vec3(0.0f);
    glm::vec3 rayFarPoint = rayOrigin + rayd * 99999.9f;
    
    float cx = sphereCenter.x;
    float cy = sphereCenter.y;
    float cz = sphereCenter.z;

    float px = rayOrigin.x;
    float py = rayOrigin.y;
    float pz = rayOrigin.z;

    float vx = rayFarPoint.x - px;
    float vy = rayFarPoint.y - py;
    float vz = rayFarPoint.z - pz;

    float A = vx * vx + vy * vy + vz * vz;
    float B = 2.0f * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
    float C = px * px - 2.0f * px * cx + cx * cx + py * py - 2.0f * py * cy + cy * cy +
                pz * pz - 2.0f * pz * cz + cz * cz - sphereRadius * sphereRadius;

    // discriminant
    float D = B * B - 4.0f * A * C;

    if ( D < 0.0f )
    {
        closestIntersection = glm::vec3(0.0f);
        normal = glm::normalize(closestIntersection - sphereCenter);
        return false;
    }

    float t1 = ( -B - sqrt( D ) ) / ( 2.0f * A );

    glm::vec3 solution1 = glm::vec3( rayOrigin.x * ( 1.0f - t1 ) + t1 * rayFarPoint.x,
                                     rayOrigin.y * ( 1.0f - t1 ) + t1 * rayFarPoint.y,
                                     rayOrigin.z * ( 1.0f - t1 ) + t1 * rayFarPoint.z );
    
    if ( D == 0.0f ) 
    { 
        closestIntersection = solution1;
        normal = glm::normalize(closestIntersection - sphereCenter);
        return true;
    }
    
    float t2 = ( -B + sqrt( D ) ) / ( 2.0f * A );
    glm::vec3 solution2 = glm::vec3( rayOrigin.x * ( 1.0f - t2 ) + t2 * rayFarPoint.x,
                                     rayOrigin.y * ( 1.0f - t2 ) + t2 * rayFarPoint.y,
                                     rayOrigin.z * ( 1.0f - t2 ) + t2 * rayFarPoint.z );

    // prefer a solution that's on the line segment itself
    if (glm::length(rayOrigin - solution1) < glm::length(rayOrigin - solution2)) 
    {
        closestIntersection = solution1;
    }
    else closestIntersection = solution2;
    
    
    normal = glm::normalize(closestIntersection - sphereCenter);
    return true;
}

glm::vec3 getRay(int pixelX, int pixelY)
{
    float x = vpWidth * ( float(pixelX) / (WINDOW_WIDTH/2) );
    float y = -vpHeight * ( float(pixelY) / (WINDOW_HEIGHT/2) );
    float z = ZNEAR;
    return glm::vec3(x, y, z);
}

void drawScene(sf::RenderWindow &window, sf::Image &frameBuffer)
{
    timeCount += 0.05f;
    for(int x = -WINDOW_WIDTH/2; x < WINDOW_WIDTH/2; ++x)
    {
        for(int y = -WINDOW_HEIGHT/2; y < WINDOW_HEIGHT/2; ++y)
        {
            //float fish_factorX = cos( (x * (R_FOV / WINDOW_WIDTH) ) - (R_FOV / 2.0f ) );
            //float fish_factorY = sin( (y  * (FOV / WINDOW_WIDTH) ) - (FOV / 2.0f) );
            
            glm::vec3 ray = getRay(x, y);
            
            sf::Color pixelColor;
            glm::vec3 intersection, normal;
            
            glm::vec3 spherePos = glm::vec3(sin(timeCount) * 2.5f, -cos(timeCount) *2.5f, sin(timeCount*3.0f) *2.0f +10.0f);
           // glm::vec3 spherePos = glm::vec3(2.5f, 2.0f, 10.0f);
            
            if(intersectsSphere(spherePos, 0.5f, ray, intersection, normal))
            {
                pixelColor = sf::Color(255, 0, 0);
                glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f));
                float dot = glm::dot(-lightDir, normal);
                dot = dot < 0.0f ? 0.0f : (dot > 1.0f ? 1.0f : dot);
                pixelColor = sf::Color(pixelColor.r * dot, pixelColor.g * dot, pixelColor.b * dot);
            }
            else pixelColor = sf::Color(255, 255, 255);
            
            frameBuffer.setPixel(x + WINDOW_WIDTH/2, y + WINDOW_HEIGHT/2, pixelColor);
        }
    }
        
    sf::Texture texture; texture.loadFromImage(frameBuffer);
    sf::Sprite sprite; sprite.setTexture(texture);
    window.draw(sprite);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");

    sf::Image frameBuffer;
    frameBuffer.create(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }

        window.clear(sf::Color::Black);
        
        drawScene(window, frameBuffer);
        window.display();
    }

    return 0;
}