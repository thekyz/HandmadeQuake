
CC=gcc
CFLAGS=-c -Wall -std=c11 -g -o0
LDFLAGS=
SOURCES=common.c q_stl.c sys_linux.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=linquake

all: $(SOURCES) $(TARGET) main

main:
	$(CC) main.c -o main -lX11 $(CCFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o linquake