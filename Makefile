CC = g++
CFLAGS = -c -std=c++14
LDFLAGS = `pkg-config opencv --cflags --libs`
SOURCES = Main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = pso

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

clean :
	rm *.o $(EXECUTABLE)
