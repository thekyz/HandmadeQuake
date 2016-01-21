
CC=gcc
CFLAGS=-c -Wall -std=c11 -g -o0
LDFLAGS=
LIBS=-lX11
SOURCES=main_x11.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=Module2

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(TARGET)