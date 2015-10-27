#include "../include/SceneReader.h"

void SceneReader::ReadScene(const Scene& scene, string filename)
{
  FILE *f;
  f = fopen(filename.c_str(), "r");
  
  AST *root = NULL;
  ANTLR(program(&root),  f);
  ASTPrint(root);
  
  fclose(f);
}