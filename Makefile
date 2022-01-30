CC ?= clang
CFLAGS = $(shell (pkg-config --cflags --libs sqlite3 gtk+-3.0)) -g
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = graph-notes

all : $(SOURCES) $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean :
	rm -f $(OBJECTS) $(OUTPUT)
