#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"

using namespace std;

class Scene
{
private:
  sf::Image frameBuffer;

  static float Fov, RFov;
  static float AspectRatio, ZNear, ViewportWidth, ViewportHeight;

  void GetRayFromPixel(int pixelX, int pixelY, Ray &ray);

  void ClearDepthBuffer();
  void ClearFrameBuffer(sf::Color clearColor);
  float GetDepthAt(int pixelX, int pixelY);
  void SetDepthAt(int pixelX, int pixelY, float depth);

public:
  static int WindowWidth, WindowHeight;

  vector<Primitive*> primitives;
  vector<float> depthBuffer;
  float timeCount;

  Scene();
  virtual ~Scene();

  void Draw(sf::RenderWindow &window);
};

#endif
