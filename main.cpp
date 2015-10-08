#include <iostream>
#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float aspectRatio = float(WINDOW_WIDTH) / WINDOW_HEIGHT;

const int FOV = 60; //degrees
const float ZNEAR = 5.0f;

float timeCount = 0.0f;

bool intersectsSphere(glm::vec3 sphereCenter, float sphereRadius, glm::vec3 rayd)
{
    glm::vec3 rayDir = glm::normalize(rayd);
    glm::vec3 rayOrigin = glm::vec3(.0f, .0f, .0f);
    
    double dot = glm::dot(rayDir, rayOrigin - sphereCenter);
    double insideRoot = pow( dot, 2.0 ) - pow( glm::length(rayOrigin - sphereCenter), 2.0 ) + pow( sphereRadius, 2.0 );
    return insideRoot >= 0.0;
}

glm::vec3 getRay(int pixelX, int pixelY)
{
    float width = ZNEAR * tan(FOV/2);
    float height = width / aspectRatio;
    
    float x = -width * ( float(pixelX) / (WINDOW_WIDTH/2) );
    float y = -height * ( float(pixelY) / (WINDOW_HEIGHT/2) );
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
            glm::vec3 ray = getRay(x, y);
            
            sf::Color pixelColor;
            if(intersectsSphere(glm::vec3(sin(timeCount) * 50.0f, 0.0f, 10.0f), 5.0f, ray))
                pixelColor = sf::Color(255, 0, 0);
            else
                pixelColor = sf::Color(255, 255, 255);
            
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