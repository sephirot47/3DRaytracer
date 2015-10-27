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

class Scene;
//struct AST;

class SceneReader
{
private:
  SceneReader() {}
  static glm::vec3 ReadVec3 (AST* vec);
  static glm::dvec3 ReadDVec3 (AST* vec);
  
public:
  virtual ~SceneReader() {}
  
  static void ReadScene(Scene& scene, string filename);
};

#endif
