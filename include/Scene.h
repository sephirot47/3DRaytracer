#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "PointLight.h"

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
  static int MSAA;
  static int WindowWidth, WindowHeight;
  static glm::vec3 ClearColor;

  vector<Primitive*> primitives;
  vector<Light*> lights;
  vector<double> depthBuffer;
  double timeCount;

  Scene();
  virtual ~Scene();

  void Draw(sf::RenderWindow &window);
  
  glm::dvec3 GetRandomVector();
  
  glm::vec3 GetPixelColor(Ray& ray, int bounces, bool inVoid);
  bool RayTrace(const Ray& ray, Intersection &intersection) const;
  static sf::Color Vec3ToColor(glm::vec3 color);
  static double GetRand() { return double(rand()%10000)/10000; }
};

#endif
