CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = src/main.cpp
TARGET = lab2

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean