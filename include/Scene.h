#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"
#include "Light.h"

using namespace std;

class Scene
{
private:
  sf::Image frameBuffer;

  static double Fov, RFov;
  static double AspectRatio, ZNear, ViewportWidth, ViewportHeight;

  void GetRayFromPixel(int pixelX, int pixelY, Ray &ray);

  void ClearDepthBuffer();
  void ClearFrameBuffer(sf::Color clearColor);
  double GetDepthAt(int pixelX, int pixelY);
  void SetDepthAt(int pixelX, int pixelY, double depth);

public:
  static int WindowWidth, WindowHeight;

  vector<Primitive*> primitives;
  vector<Light*> lights;
  vector<double> depthBuffer;
  double timeCount;

  Scene();
  virtual ~Scene();

  void Draw(sf::RenderWindow &window);
  bool RayTrace(const Ray& ray, Intersection &intersection) const;
};

#endif
