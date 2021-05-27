CFLAGS := -Wall -Werror -std=c++17
CPPFLAGS := -MMD 
CXX := g++

TARGET := bin/GameOfLife

SOURCES := $(wildcard src/gameOfLife/*.cpp)
LIBSOURCES := $(wildcard src/lib/*.cpp)
LIBMSOURCES := $(wildcard src/mlib/*.cpp)

LIBOBJ := $(patsubst src/lib/%.cpp, obj/src/%.o, $(LIBSOURCES))
LIB := obj/lib/functionLib.a 

MLIBOBJ := $(patsubst src/mlib/%.cpp, obj/src/%.o, $(LIBMSOURCES))
MLIB := obj/mlib/methodsLib.a 

OBJ := $(patsubst src/gameOfLife/%.cpp, obj/src/%.o, $(SOURCES))

LIBS= -DSFML_STATIC -lsfml-graphics -lsfml-window 

TEST := $(wildcard test/*.cpp) 
TESTOBJ := $(patsubst test/%.cpp, obj/test/%.o, $(TEST))
TESTTARGET := bin/TestGameOfLife
CTEST := thirdparty/ctest.h

all:$(TARGET)

$(TARGET): $(OBJ) 
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LIBS) 
	
$(LIB): $(LIBOBJ)
	ar rcs $@ $^

$(MLIB): $(MLIBOBJ)
	ar rcs $@ $^

obj/lib/%.o: src/lib/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@  -I$(SFMLINCLUDE) -Isrc/lib -Isrc/mlib

obj/mlib/%.o: src/mlib/%.cpp 
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c  $< -o $@  -I$(SFMLINCLUDE) -Isrc/lib -Isrc/mlib

obj/src/%.o: src/gameOfLife/%.cpp 
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c  $< -o $@  -I$(SFMLINCLUDE) -Isrc/lib -Isrc/mlib
	
test: $(TESTTARGET)
	./$(TESTTARGET)

$(TESTTARGET): $(TESTOBJ) $(CTEST) $(LIB)
	$(CXX) $(CPPFLAGS) $(CFLAGS)  $(TESTOBJ) -o $@ -L$(LIB) -I src/lib -Isrc/mlib -Ithirdparty

obj/test/%.o: test/%.cpp $(CTEST)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c  $< -o $@ -Isrc/lib -Isrc/mlib -Ithirdparty
		
run: $(TARGET)
	./bin/GameOfLife
	
clean:
	find . -name "*.o" -exec rm '{}' \;
	find . -name "*.d" -exec rm '{}' \;
	find . -name "*.a" -exec rm '{}' \;
	find ./bin -type f -name "GameOfLife" -exec rm -f '{}' \;
	find ./bin -type f -name "TestGameOfLife" -exec rm -f '{}' \;
	find ./src/mlib -type f -name "logic" -exec rm -f '{}' \;
	
format:
	cd src; find . -name "*.cpp" -exec clang-format -i {} \; 
	cd src; find . -name "*.h" -exec clang-format -i {} \; 
	
.PHONY: clean test run all format