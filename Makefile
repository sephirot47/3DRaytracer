all: main.exe

main.o: main.cpp
	g++ -O2 -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -c main.cpp -o main.o
	
main.exe: main.o Sphere.o Ray.o Primitive.o
	g++ -O2 main.o Primitive.o Sphere.o Ray.o -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o main.exe
	
Primitive.o: Primitive.cpp
	g++ -O2 -c Primitive.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o Primitive.o
	
Sphere.o: Sphere.cpp
	g++ -O2 -c Sphere.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o Sphere.o

Ray.o: Ray.cpp
	g++ -O2 -c Ray.cpp -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o Ray.o	

clean:
	rm -rf *.o *.exe
