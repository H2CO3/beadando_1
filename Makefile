OPSYS = $(shell uname | tr '[[:upper:]]' '[[:lower:]]')

ifeq ($(OPSYS), darwin)
	CXX = clang++
else
	CXX = g++
endif

LD = $(CXX)


WARNINGS = -Wall -Wextra -Wno-unused-parameter -pedantic
INCLUDES = -I/usr/local/Cellar/sdl_ttf/2.0.11/include -I /usr/local/Cellar/sdl/1.2.15/include/SDL/
DEFINES = -DWORKAROUND_TO_COMPENSATE_THE_SDL_DEVELOPERS_BEING_STUPID
LIBDIRS = -L /usr/local/Cellar/sdl_ttf/2.0.11/lib/
LIBS = $(shell sdl-config --libs) -lSDL_ttf Sparkling/bld/libspn.a

CXXFLAGS = -c -std=c++98 $(sdl-config --cflags) $(WARNINGS) $(INCLUDES) $(DEFINES) -O2 -flto
LDFLAGS = $(LIBDIRS) $(LIBS) -O2 -flto

TARGET = beadando_1
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp libflugigfx/*.cpp libflugigfx-spn/*.cpp))

all: spnlib $(TARGET)

spnlib:
	make BUILD=release -C Sparkling

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)
	make clean -C Sparkling

.PHONY: all clean

