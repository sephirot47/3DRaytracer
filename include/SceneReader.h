#ifndef SCENE_READER_H
#define SCENE_READER_H

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

#include <fstream>
#include <string>

using namespace std;

class SceneReader
{
private:
  SceneReader() {}
  
public:
  virtual ~SceneReader() {}
  
  static void ReadScene(const Scene& scene, string filename);
};

#endif
