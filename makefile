CC := g++
FLAGS := 
# -O3 -std=c++17 -g -Wall -Wextra -pedantic-errors
SFML_LIBS := $(shell pkg-config sfml-all --libs)
TARGET := fish_game

SRCS := $(wildcard src/*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS1 := $(notdir $(OBJS))
OBJS1 := $(addprefix obj/, $(OBJS1))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(OBJS1) $(FLAGS) $(SFML_LIBS) -o $@ 
%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $(addprefix obj/, $(notdir $(patsubst %.cpp,%.o,$<)))
clean:
	rm -rf $(TARGET) obj/*.o
	
.PHONY: all clean
