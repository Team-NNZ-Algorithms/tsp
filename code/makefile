CC=g++
CFLAGS=-std=c++11 -Wall -g

SRC_DIR := src
OBJ_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

tsp.out: tsp.cpp $(OBJ_FILES) 
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	 mkdir -p $@

.PHONY=clean run

run: tsp.out data/tsp_example_1.txt
	./tsp.out data/tsp_example_1.txt

clean:
	rm -Rf bin/
	rm -Rf *.out