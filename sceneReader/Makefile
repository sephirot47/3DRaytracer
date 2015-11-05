all: sceneReader.o scan.o err.o

sceneReader.o: dlg scan.cpp mode.h sceneReader.g
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c sceneReader.c -o sceneReader.o

scan.o: dlg scan.cpp
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c scan.cpp -o scan.o

err.o: dlg err.cpp
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c err.cpp -o err.o

dlg: antlr tokens.h parser.dlg
	dlg -ci parser.dlg scan.cpp
	mv err.c err.cpp
	
antlr: sceneReader.g
	antlr -gt sceneReader.g
	
clean: 
	rm -rf *.cpp *.o *.h *.exe *.dlg *~
	clear
	clear
