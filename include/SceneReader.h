#ifndef SCENE_READER_H
#define SCENE_READER_H

#include "glm/glm.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Material.h"
#include "Sphere.h"
#include "Cube.h"
#include "Ray.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#include <map>
#include <fstream>
#include <string>

using namespace std;

class Scene;

class SceneReader
{
private:
    
  SceneReader() {}
  
  static map<string, Material*> materialsMap;
  static glm::vec3 ReadVec3 (void* vec);
  static glm::dvec3 ReadDVec3 (void* vec);
  
  static void ReadCube(Scene& scene, void* astCube);
  static void ReadSphere(Scene& scene, void* astSphere);
  static void ReadDLight(Scene& scene, void* astDLight);
  static void ReadPLight(Scene& scene, void* astPLight);
  static void ReadMaterial(void* astMaterial);
  
public:
  virtual ~SceneReader() {}
  static void ReadScene(Scene& scene, string filename);
};

#endif
