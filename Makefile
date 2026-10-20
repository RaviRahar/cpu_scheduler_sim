CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic
TARGET := cpu_scheduler_sim
DEPENDENCIES := main.cpp definations.h Process.cpp Process_Creator.cpp Scheduler.cpp Simulator.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) status.txt processes.txt
