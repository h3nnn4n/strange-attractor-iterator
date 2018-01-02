CFLAGS=-Ofast -lm -lpng -Wall
LDFLAGS =-shared -fPIC -Wl,-soname #,libstrange.so

CC=gcc

SOURCES=color.c \
		magic.c \
		strange.c \

SOURCE_BIN=cliff.c
EXECUTABLE=cliff
TARGET_LIB = libstrange.so
LIB_O = strange.o

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_BIN=$(SOURCE_BIN:.c=.o)

all: $(SOURCES) $(SOURCE_BIN) $(EXECUTABLE) $(TARGET_LIB)

$(EXECUTABLE): $(OBJECTS) $(OBJECTS_BIN)
	$(CC) $(CFLAGS) $(OBJECTS) $(OBJECTS_BIN) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -c -fPIC -o $@

$(TARGET_LIB):
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) $(OBJECTS) -lc

.PHONY: clean
clean:
	$(RM) $(OBJECTS_BIN) $(OBJECTS) $(EXECUTABLE) $(TARGET_LIB)
