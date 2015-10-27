all: sceneReader.exe

sceneReader.exe: dlg scan.c mode.h
	g++ -std=c++11 -I/usr/include/pccts -o sceneReader.exe sceneReader.c scan.c err.c
	clear
	clear
	./sceneReader.exe < scene.txt
	
antlr: sceneReader.g
	antlr -gt sceneReader.g
	
dlg: antlr err.c tokens.h parser.dlg
	dlg -ci parser.dlg scan.c
	
clean: 
	rm -rf *.c *.o *.h *.exe *.dlg *~
	clear
	clear
