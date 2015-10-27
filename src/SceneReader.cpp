#include "../include/SceneReader.h"
//#include "../sceneReader/sceneReader.c"

void SceneReader::ReadScene(const Scene& scene, string filename)
{
  ifstream input;
  input.open(filename.c_str());
  
  root = NULL;
  ANTLR(program(&root),  stdin);
  ASTPrint(root);
  
  input.close();
}