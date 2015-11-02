#include <iostream>

#define EPSILON 0.00001

#include "../include/glm/glm.hpp"
#include <SFML/Graphics.hpp>

#include "../include/Scene.h"
#include "../include/SceneReader.h"

using namespace std;
bool paused = false;

int main(int argc, char **args)
{ 
  
  string sceneFileName = "";
  if(argc >= 2) sceneFileName = args[1];

  Scene scene;

  if(sceneFileName != "") SceneReader::ReadScene(scene, sceneFileName);
  scene.Render();

  sf::RenderWindow window(sf::VideoMode(Scene::GetWindowWidth()/Scene::GetMSAA(),
                                        Scene::GetWindowHeight()/Scene::GetMSAA()),
                                        "3D Raytracer",
                                        sf::Style::Titlebar | sf::Style::Close);
      
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
     scene.Draw(window);
  }
  return 0;
}
