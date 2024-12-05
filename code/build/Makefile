CXX = g++
CFLAGS = -g
DEBUGGER = gdb

EXE_DIR = 
SCR_DIR = ../scripts
HEAD_DIR = ../scripts/headers
BUILD_DIR = 

FILES = scripts/ttpMain.cpp scripts/FFDH.cpp
OBJS = BLMain.o generate.o ttpMain.o  FFDH.o BL.o generate_main.o
TARGET = ttpMain BLMain generate rec_gen
EXE = ttpMain.exe generate.exe BLMain.exe

# 默认目标
all: $(TARGET)

ttpMain: ttpMain.o FFDH.o
	$(CXX) -o $@  $^

BLMain: BLMain.o BL.o generate.o
	$(CXX) -o $@  $^

generate: generate.o generate_main.o
	$(CXX) -o $@  $^

rec_gen: $(SCR_DIR)/rec_gen.cpp
	$(CXX) -o $@ $<

# 调试目标
debug: 
	$(CXX) -o $(TARGET) $(FILES) $(CFLAGS)
	$(DEBUGGER) $(TARGET)

# 编译 .cpp 文件为 .o 文件并放入 build 目录
ttpMain.o: $(SCR_DIR)/ttpMain.cpp $(HEAD_DIR)/ttpHeader.h
	$(CXX) $(CFLAGS) -c $< -o $@

FFDH.o: $(SCR_DIR)/FFDH.cpp $(HEAD_DIR)/ttpHeader.h
	$(CXX) $(CFLAGS) -c $< -o $@

BLMain.o : $(SCR_DIR)/BLMain.cpp $(HEAD_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

BL.o : $(SCR_DIR)/BL.cpp $(HEAD_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

generate.o : $(SCR_DIR)/generate.cpp $(HEAD_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

generate_main.o : $(SCR_DIR)/generate_main.cpp $(HEAD_DIR)/header.h
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f test $(OBJS) $(TARGET)
