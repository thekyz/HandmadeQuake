
CC=gcc
CFLAGS=-c -Wall -std=c99 -g -o0
LDFLAGS=
SOURCES=common.c q_stl.c sys_linux.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=linquake

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o linquake