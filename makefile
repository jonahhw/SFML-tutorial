# makefile for the sfml tutorial
# compiler can be changed by changing the "Compiler" variable and potentially changing the syntax
# compile by running `make`

Compiler = g++
SFMLLibs = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
OBJs = obj/main.o obj/Animation.o obj/Player.o obj/Collider.o obj/Platform.o

sfmltut: $(OBJs)
	$(Compiler) $(OBJs) $(SFMLLibs) -o sfmltut

obj/main.o: src/main.cpp obj/Platform.o obj/Player.o
	$(Compiler) -o obj/main.o -c src/main.cpp

obj/Player.o: src/Player.cpp src/Player.h obj/Animation.o obj/Collider.o
	$(Compiler) -o obj/Player.o -c src/Player.cpp

obj/Animation.o: src/Animation.cpp src/Animation.h
	$(Compiler) -o obj/Animation.o -c src/Animation.cpp

obj/Collider.o: src/Collider.cpp src/Collider.h
	$(Compiler) -o obj/Collider.o -c src/Collider.cpp

obj/Platform.o: src/Platform.cpp src/Platform.h obj/Collider.o
	$(Compiler) -o obj/Platform.o -c src/Platform.cpp