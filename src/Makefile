# Declaration of variables
CC = g++
CC_FLAGS = -w -g -std=c++11

# File names
EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) ../bin/*.o -o ../bin/$(EXEC) -lpthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system 

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o ../bin/$@ 

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
