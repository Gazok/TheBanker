FLAGS = #-m32
CXXFLAGS = $(FLAGS) -c -std=c++0x -O3
LDFLAGS =  $(FLAGS) -lsfml-graphics -lsfml-window -lsfml-system 
VPATH = src/
PROGRAM = WallStreet
SOURCES = main.cpp Game.cpp Graphics.cpp GameState.cpp Entity.cpp Keyboard.cpp \
		  DialogueTree.cpp DialogueBox.cpp Map.cpp DialogueState.cpp Player.cpp \
		  MainState.cpp Victim.cpp Warden.cpp Table.cpp Boss.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS)
