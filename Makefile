OPTIONS=-O2 -I/usr/include/pccts -Wno-write-strings 
	
all: main.exe

main.exe: obj/main.o obj/Scene.o obj/Sphere.o obj/Ray.o obj/Primitive.o obj/Cube.o obj/DirectionalLight.o obj/PointLight.o  obj/Light.o obj/Material.o obj/SceneReader.o
	g++ $(OPTIONS) obj/main.o obj/Scene.o obj/Primitive.o obj/Sphere.o obj/Cube.o obj/Ray.o obj/DirectionalLight.o obj/PointLight.o obj/Light.o obj/Material.o obj/SceneReader.o -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o main.exe
	./main.exe

obj/main.o: src/main.cpp
	g++ $(OPTIONS) -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -c src/main.cpp -o obj/main.o

obj/Primitive.o: src/Primitive.cpp
	g++ $(OPTIONS) -c src/Primitive.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Primitive.o

obj/Sphere.o: src/Sphere.cpp
	g++ $(OPTIONS) -c src/Sphere.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Sphere.o

obj/Cube.o: src/Cube.cpp
	g++ $(OPTIONS) -c src/Cube.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Cube.o

obj/Scene.o: src/Scene.cpp
	g++ $(OPTIONS) -c src/Scene.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Scene.o

obj/Ray.o: src/Ray.cpp
	g++ $(OPTIONS) -c src/Ray.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Ray.o

obj/Light.o: src/Light.cpp
	g++ $(OPTIONS) -c src/Light.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Light.o

obj/DirectionalLight.o: src/DirectionalLight.cpp
	g++ $(OPTIONS) -c src/DirectionalLight.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/DirectionalLight.o

obj/PointLight.o: src/PointLight.cpp
	g++ $(OPTIONS) -c src/PointLight.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/PointLight.o

obj/Material.o: src/Material.cpp
	g++ $(OPTIONS) -c src/Material.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o obj/Material.o

obj/SceneReader.o: src/SceneReader.cpp obj/parser.o
	g++ $(OPTIONS) -c src/SceneReader.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  obj/parser.o -o obj/SceneReader.o 

obj/parser.o: dlg sceneReader/scan.c sceneReader/mode.h
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -o obj/parser.o sceneReader/sceneReader.c sceneReader/scan.c sceneReader/err.c
	
antlr: sceneReader/sceneReader.g
	cd sceneReader; antlr -gt sceneReader.g
	
dlg: antlr sceneReader/err.c sceneReader/tokens.h sceneReader/parser.dlg
	cd sceneReader; dlg -ci parser.dlg scan.c

clean:
	rm -rf obj/*.o *.exe
