all: sceneReader.o scan.o err.o

sceneReader.o: dlg scan.c mode.h sceneReader.g
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c sceneReader.c -o sceneReader.o

scan.o: dlg scan.c
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c scan.c -o scan.o

err.o: dlg err.c
	g++ -std=c++11 -Wno-write-strings -I/usr/include/pccts -c err.c -o err.o

dlg: antlr err.c tokens.h parser.dlg
	dlg -ci parser.dlg scan.c
	
antlr: sceneReader.g
	antlr -gt sceneReader.g
	
clean: 
	rm -rf *.c *.o *.h *.exe *.dlg *~
	clear
	clear
