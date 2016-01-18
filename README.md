# 3DRaytracer
## 3D Raytracer in C++ from scratch.
### Currently supporting:  <br />
-Indirect lighting  <br />
-Reflection  <br />
-Refraction  <br />
-Transparency  <br />
-Depth of field  <br />
-Scene file format with materials definition and materials inheritance

### You can render a scene executing: 
  make   <br />
  ./main.exe  sceneFile   <br />

There are sceneFiles in the <b>"exampleScenes"</b> directory.
Sadly, to make the file parser, we used quite an ancient version of ANTLR, and it's very difficult to find the libs to compile it :(
