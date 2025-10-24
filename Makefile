CC = g++
TARGET = ./ascii_game.exe

SRCS = main.cpp utility.cpp player.cpp bomb.cpp gameobject.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)