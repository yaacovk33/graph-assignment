// email: yaacovkrawiec@gmail.com
# Makefile

# === COMPILER & FLAGS ===
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++11 -I./include

# === DIRECTORIES ===
SRC_DIR = ./src
INCLUDE_DIR = ./include

# === OBJECT FILES ===
OBJS = $(SRC_DIR)/Graph.o $(SRC_DIR)/Algorithms.o

# Main program object
MAIN_OBJ = $(SRC_DIR)/Main.o

# Test program object
TEST_OBJ = $(SRC_DIR)/tests.o

# === DEFAULT TARGET ===
all: Main

# === BUILD AND LINK THE MAIN PROGRAM ===
Main: $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o Main $(OBJS) $(MAIN_OBJ)

# === BUILD AND LINK THE TEST PROGRAM ===
test: $(OBJS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o test_exec $(OBJS) $(TEST_OBJ)
	./test_exec

# === VALGRIND CHECK ON MAIN ===
valgrind: Main
	valgrind --leak-check=full ./Main

# === CLEAN ALL ARTIFACTS ===
clean:
	rm -f Main test_exec $(SRC_DIR)/*.o

# === COMPILATION RULES FOR EACH .cpp ===

$(SRC_DIR)/Graph.o: $(SRC_DIR)/Graph.cpp $(INCLUDE_DIR)/Graph.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Graph.cpp -o $(SRC_DIR)/Graph.o

$(SRC_DIR)/Algorithms.o: $(SRC_DIR)/Algorithms.cpp $(INCLUDE_DIR)/Algorithms.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Algorithms.cpp -o $(SRC_DIR)/Algorithms.o

$(SRC_DIR)/Main.o: $(SRC_DIR)/Main.cpp $(INCLUDE_DIR)/Graph.h $(INCLUDE_DIR)/Algorithms.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Main.cpp -o $(SRC_DIR)/Main.o

$(SRC_DIR)/tests.o: $(SRC_DIR)/tests.cpp $(INCLUDE_DIR)/Graph.h $(INCLUDE_DIR)/Algorithms.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/tests.cpp -o $(SRC_DIR)/tests.o
