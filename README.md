# 3DRaytracer
3D Raytracer in C++ from scratch.
Currently supporting:
-Indirect lighting
-Reflection
-Refraction
-Transparency
-Depth of field
-Scene file format with materials definition and materials inheritance

You can render a scene doing: 
  make
  ./main.exe  sceneFile

There are sceneFiles in the "exampleScenes" directory.
Sadly, to make the file parser, we used quite an ancient version of ANTLR, and it's very difficult to find the libs to compile it :(
