OBJs = obj/main.o obj/Animation.o obj/Player.o
Compiler = g++
SFMLLibs = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

sfmltut: $(OBJs)
	$(Compiler) $(OBJs) $(SFMLLibs) -o sfmltut

obj/main.o: src/main.cpp
	$(Compiler) -o obj/main.o -c src/main.cpp

obj/Animation.o: src/Animation.cpp
	$(Compiler) -o obj/Animation.o -c src/Animation.cpp

obj/Player.o: src/Player.cpp src/Animation.o
	$(Compiler) -o obj/Player.o -c src/Player.cpp