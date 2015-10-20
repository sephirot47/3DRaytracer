#include <iostream>

#include "../include/glm/glm.hpp"
#include <SFML/Graphics.hpp>

#include "../include/Scene.h"

using namespace std;
bool paused = false;

int main()
{
  Scene scene;
  sf::RenderWindow window(sf::VideoMode(Scene::WindowWidth, Scene::WindowHeight), "3D Raycaster");

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();
      
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                paused = !paused;
            }
        }
    }
    if(!paused) scene.Draw(window);
  }
  return 0;
}