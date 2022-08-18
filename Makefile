CXX = g++

# -pipe -O2 -Werror
CFLAGS  := -g -Wall -Wextra -Wpedantic -Werror

SFML_FLAGS := -IHeaderFiles/ -ISFML/include/ -LSFML/lib -lsfml-window-d -lsfml-graphics-d -lsfml-audio-d -lsfml-system-d

link: obj/main.o obj/player.o obj/tiles.o obj/loadGraphics.o obj/terrainGeneration.o
	$(CXX) $^ $(SFML_FLAGS) $(CFLAGS) -o bin/main.exe

obj/main.o: src/main.cpp
	$(CXX) $^ -c $(SFML_FLAGS) $(CFLAGS) -o $@

obj/player.o: src/player.cpp
	$(CXX) $^ -c $(SFML_FLAGS) $(CFLAGS) -o $@

obj/tiles.o: src/tiles.cpp
	$(CXX) $^ -c $(SFML_FLAGS) $(CFLAGS) -o $@

obj/loadGraphics.o: src/loadGraphics.cpp
	$(CXX) $^ -c $(SFML_FLAGS) $(CFLAGS) -o $@

obj/terrainGeneration.o: src/terrainGeneration.cpp
	$(CXX) $^ -c $(SFML_FLAGS) $(CFLAGS) -o $@

all:
	$(CXX) src/main.cpp -c $(SFML_FLAGS) $(CFLAGS) -o obj/main.o
	$(CXX) src/player.cpp -c $(SFML_FLAGS) $(CFLAGS) -o obj/player.o
	$(CXX) src/tiles.cpp -c $(SFML_FLAGS) $(CFLAGS) -o obj/tiles.o
	$(CXX) src/loadGraphics.cpp -c $(SFML_FLAGS) $(CFLAGS) -o obj/loadGraphics.o
	$(CXX) src/terrainGeneration.cpp -c $(SFML_FLAGS) $(CFLAGS) -o obj/terrainGeneration.o
	$(CXX) obj/* $(SFML_FLAGS) $(CFLAGS) -o bin/main.exe

clean:
	rm -rf obj/*