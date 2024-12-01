CXX = g++
CFLAGS = -g
DEBUGGER = gdb
SCR_DIR = ./scripts
BUILD_DIR = ./build

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/func.o $(BUILD_DIR)/generate.o

test: $(OBJS)
	$(CXX) -o test 	$^

$(BUILD_DIR)/main.o : $(SCR_DIR)/main.cpp $(SCR_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/func.o : $(SCR_DIR)/func.cpp $(SCR_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/generate.o : $(SCR_DIR)/generate.cpp $(SCR_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f test $(OBJS)