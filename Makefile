CXX = g++

# -pipe -O2 -static -static-libgcc -static-libstdc++
CFLAGS  := -g -Wall

SFML_FLAGS := -IHeaderFiles/ -ISFML/include/ -LSFML/lib -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d -lsfml-system-d

link: obj/main.o obj/player.o obj/tile.o obj/tiles.o obj/loadGraphics.o 
	$(CXX) $^ $(SFML_FLAGS) $(CFLAGS) -o bin/main.exe

obj/main.o: src/main.cpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) src/main.cpp -c -o obj/main.o

obj/player.o: src/player.cpp Headerfiles/player.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) src/player.cpp -c -o obj/player.o

obj/tile.o : src/tile.cpp Headerfiles/tileMap.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) src/tile.cpp -c -o obj/tile.o

obj/tiles.o: src/tile.cpp src/tiles.cpp Headerfiles/tileMap.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) src/tiles.cpp -c -o obj/tiles.o

obj/loadGraphics.o: src/loadGraphics.cpp Headerfiles/loadAssets.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) src/loadGraphics.cpp -c -o obj/loadGraphics.o

clean:
	$(RM) *.o