.PHONY: all clean run bin build

CXX= g++
CXXFLAGS= -Wall -std=c++17 -Iinclude

SFML_LIBS= -lsfml-graphics -lsfml-window -lsfml-system

VERBOSE ?= 0
ifeq ($(VERBOSE), 1)
    Q = 
else
    Q = @
endif

ifeq ($(OS), Windows_NT)
    EXE := .exe
    RM := cmd /C del /Q /F
    BUILD_FOLDER := if not exist build mkdir build
    BIN_FOLDER := if not exist bin mkdir bin
    CLEAN = $(RM) bin\\*.exe build\\*.o 2>nul >nul
    RUN_CMD = $(TARGET)
else
    EXE :=
    RM := rm -f
    BUILD_FOLDER := mkdir -p build
    BIN_FOLDER := mkdir -p bin
    CLEAN = $(RM) bin/*.exe build/*.o
    RUN_CMD = ./$(TARGET)
endif

TARGET = bin/main$(EXE)

SRCS= $(wildcard demo/*.cpp)
OBJS= $(patsubst demo/%.cpp, build/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | bin
	$(Q)$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS) 

build/%.o: demo/%.cpp | build
	$(Q)$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	$(Q)$(BIN_FOLDER)

build:
	$(Q)$(BUILD_FOLDER)

clean:
	$(Q)echo "Cleaning..."
	$(Q)$(CLEAN)

run: $(TARGET)
	$(Q)$(RUN_CMD)