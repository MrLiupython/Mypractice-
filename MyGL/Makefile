OBJECTS = hello.o glad.o
TARGET = hello_demo
CC = g++
CFLAGS = -Wall -Wextra -Wunreachable-code -ggdb -O0
SOURCE = src/hello.cpp src/glad.c
INC_PATH = -I include
LIB_PATH = -L lib/ -l glfw3 -lGL -lm -ldl -lXinerama -lXrandr -lXi -l Xcursor -l X11 -lXxf86vm -lpthread

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INC_PATH) $(OBJECTS) $(LIB_PATH) -o $(TARGET)
$(OBJECTS): $(SOURCE)
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) -c $(SOURCE)

clean:
	rm $(OBJECTS)

