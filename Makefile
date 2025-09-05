.PHONY: all clean run bin build

CXX= g++
CXXFLAGS= -Wall -std=c++17 -Iinclude

LIBS= -lsfml-graphics -lsfml-window -lsfml-system

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

SRCS= $(wildcard src/*.cpp)
OBJS= $(patsubst src/%.cpp, build/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | bin
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

build/%.o: src/%.cpp | build
	@$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	@$(BIN_FOLDER)

build:
	@$(BUILD_FOLDER)

clean:
	@echo "Cleaning..."
	@$(CLEAN)

run: $(TARGET)
	@$(RUN_CMD)