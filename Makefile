CFLAGS=-fPIC -Ofast -lm -lpng -Wall -Wno-unused-but-set-variable -Wno-unused-variable
LDFLAGS=-shared -fPIC -Wl,-soname #,libstrange.so

CC=gcc

SOURCES=color.c \
		magic.c

SOURCE_BIN=cliff.c
EXECUTABLE=cliff
TARGET_LIBS = libcolor.so \
			  libmagic.so

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_BIN=$(SOURCE_BIN:.c=.o)

all: $(SOURCES) $(SOURCE_BIN) $(EXECUTABLE) $(TARGET_LIBS)

$(EXECUTABLE): $(OBJECTS) $(OBJECTS_BIN)
	$(CC) $(CFLAGS) $(OBJECTS) $(OBJECTS_BIN) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

$(TARGET_LIBS):
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) -lc

.PHONY: clean
clean:
	$(RM) $(OBJECTS_BIN) $(OBJECTS) $(EXECUTABLE) $(TARGET_LIBS)
