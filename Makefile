CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = pfsp
SRC_DIR = src
OBJ_DIR = build

SOURCES = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/instance.cpp \
	$(SRC_DIR)/instance_reader.cpp \
	$(SRC_DIR)/random_search.cpp \
	$(SRC_DIR)/neh.cpp \
	$(SRC_DIR)/genetic_algorithm.cpp \
	$(SRC_DIR)/metrics.cpp \
	$(SRC_DIR)/experiments.cpp

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean