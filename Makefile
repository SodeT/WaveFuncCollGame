CXX = g++

# -pipe -O2 -static -static-libgcc -static-libstdc++
CFLAGS  := -g -Wall

SFML_FLAGS := -IHeaderFiles/ -ISFML/include/ -LSFML/lib -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d -lsfml-system-d

link: main.o player.o tile.o tiles.o loadGraphics.o
	$(CXX) $^ $(SFML_FLAGS) $(CFLAGS) -o bin/main.exe

obj/%.o: main.cpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) $^ -c 

obj/%.o: player.cpp Headerfiles/player.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) $^ -c

obj/%.o: tile.cpp tiles.cpp Headerfiles/tileMap.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) $^ -c

obj/%.o: loadGraphics.cpp Headerfiles/loadAssets.hpp
	$(CXX) $(SFML_FLAGS) $(CFLAGS) $^ -c

clean:
	$(RM) *.o