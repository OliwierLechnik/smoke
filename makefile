all:
	g++ -c main.cpp
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system
	./main
win64:
	x86_64-w64-mingw32-g++ -c main.cpp -o main.bin -I /usr/share/SFML/include/
	x86_64-w64-mingw32-g++ main.bin -o main.exe -lsfml-graphics -lsfml-window -lsfml-system