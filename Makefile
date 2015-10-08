all: main.exe

main.o: main.cpp
	g++ -O2 -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -c main.cpp -o main.o
	
main.exe: main.o
	g++ -O2 main.o -std=c++11 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system  -o main.exe

clean:
	rm -rf *.o *.exe
