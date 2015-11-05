#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>

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

  static double AspectRatio, ZNear, ViewportWidth, ViewportHeight;
  static glm::dvec3 CameraPosition, CameraRotation;
  static double Fov, RFov, DepthOfField;
  static int MSAA, WindowWidth, WindowHeight;

  void GetRayFromPixel(int pixelX, int pixelY, Ray &ray);

  void ClearDepthBuffer();
  void ClearFrameBuffer(sf::Color clearColor);
  double GetDepthAt(int pixelX, int pixelY);
  void SetDepthAt(int pixelX, int pixelY, double depth);
  void ApplyDepthOfField();
  void GetGaussianKernel(int r, vector < vector<double> >& kernel);
  glm::vec3 GetPixelColor(Ray& ray, int bounces, bool inVoid, bool indirectLight = false);
  glm::vec3 GetIndirectLightning(const Intersection &intersection, glm::vec3 ownColor);
  vector<glm::dvec3> sphereVectors;
  void RenderColumns(int n);
  
public:

  static bool DepthOfFieldEnabled;

  static glm::vec3 ClearColor;
  static double InfiniteDepth;

  vector<Primitive*> primitives;
  vector<Light*> lights;
  vector<double> depthBuffer;
  double timeCount;

  Scene();
  virtual ~Scene();

  void Draw(sf::RenderWindow &window);
  void Render();
  
  glm::dvec3 GetRandomVector();
  
  void SetCamera(glm::dvec3 CameraPosition, glm::dvec3 CameraRotation, double FOV, double DepthOfField, int MSAA, int WindowWidth, int WindowHeight);

  
  bool RayTrace(const Ray& ray, Intersection &intersection) const;
  static sf::Color Vec3ToColor(glm::vec3 color);
  static glm::vec3 ColorToVec3(sf::Color color);
  static double GetRand() { return double(rand()%10000)/10000; }

  static double GetFov() { return Fov; }
  static double GetDepthOfField() { return DepthOfField; }
  static int GetMSAA() { return MSAA; }
  static int GetWindowWidth() { return WindowWidth; }
  static int GetWindowHeight() { return WindowHeight; }
};

#endif
