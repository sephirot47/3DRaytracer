#include <iostream>

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>

#include "Sphere.h"
#include "Ray.h"

using namespace std;

const int WINDOW_WIDTH = 450;
const int WINDOW_HEIGHT = 350;
const float ASPECT_RATIO = float(WINDOW_WIDTH) / WINDOW_HEIGHT;

const int FOV = 60; //degrees
const float R_FOV = FOV * 3.1415926535f/180.0f;

const float ZNEAR = 5.0f;
const float VP_WIDTH = ZNEAR * tan(R_FOV/2);
const float VP_HEIGHT = VP_WIDTH / ASPECT_RATIO;

float timeCount = 0.0f;

void getRay(int pixelX, int pixelY, Ray &ray)
{
  float x =  VP_WIDTH * ( float(pixelX) / (WINDOW_WIDTH/2) );
  float y = -VP_HEIGHT * ( float(pixelY) / (WINDOW_HEIGHT/2) );
  float z = ZNEAR;

  ray.dir = glm::vec3(x,y,z);
}

void drawScene(sf::RenderWindow &window, sf::Image &frameBuffer)
{
    Sphere sphere(glm::vec3(sin(timeCount) * 2.5f, -cos(timeCount) *2.5f, sin(timeCount*3.0f) *2.0f +10.0f),  0.5f);
	
    timeCount += 0.05f;
    for(int x = -WINDOW_WIDTH/2; x < WINDOW_WIDTH/2; ++x)
    {
      for(int y = -WINDOW_HEIGHT/2; y < WINDOW_HEIGHT/2; ++y)
      {
	  //float fish_factorX = cos( (x * (R_FOV / WINDOW_WIDTH) ) - (R_FOV / 2.0f ) );
	  //float fish_factorY = sin( (y  * (FOV / WINDOW_WIDTH) ) - (FOV / 2.0f) );

	Ray ray; getRay(x, y, ray);
	
	sf::Color pixelColor;
	glm::vec3 intersection, normal;
	
	if(sphere.GetIntersection(ray, intersection, normal))
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Raycaster");

    sf::Image frameBuffer;
    frameBuffer.create(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
	if (event.type == sf::Event::Closed) window.close();
      }

      window.clear(sf::Color::Black);
      
      drawScene(window, frameBuffer);
      window.display();
    }

    return 0;
}