CC = g++
CFLAGS = -c -std=c++14
LDFLAGS =
SOURCES = Main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = pso

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

clean :
	rm *.o $(EXECUTABLE)
