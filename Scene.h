#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#include "Sphere.h"
#include "Ray.h"

using namespace std;

class Scene
{
private:
  sf::Image frameBuffer;
  
  static float Fov, RFov;
  static float AspectRatio, ZNear, ViewportWidth, ViewportHeight;

  void GetRayFromPixel(int pixelX, int pixelY, Ray &ray);
  
public:
  static int WindowWidth, WindowHeight;
    
  vector<Primitive*> primitives;
  float timeCount;
    
  Scene();
  virtual ~Scene();
  
  void Draw(sf::RenderWindow &window);
};

#endif