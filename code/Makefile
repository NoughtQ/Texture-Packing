CXX = g++
CFLAGS = -g
DEBUGGER = gdb

HEADER = scripts/ttpHeader.h
FILES = scripts/ttpMain.cpp scripts/FFDH.cpp
OBJS = build/ttpMain.o build/FFDH.o
TARGET = ttpMain
EXE = ttpMain.exe generate.exe

# 默认目标
all: $(TARGET)

# 目标文件生成
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# 生成可执行文件
generate:
	$(CXX) -o generate scripts/generate.cpp $(CFLAGS)

# 调试目标
debug: 
	$(CXX) -o $(TARGET) $(FILES) $(CFLAGS)
	$(DEBUGGER) $(TARGET)

# 编译 .cpp 文件为 .o 文件并放入 build 目录
build/ttpMain.o: scripts/ttpMain.cpp $(HEADER)
	$(CXX) -c scripts/ttpMain.cpp -o build/ttpMain.o $(CFLAGS)

build/FFDH.o: scripts/FFDH.cpp $(HEADER)
	$(CXX) -c scripts/FFDH.cpp -o build/FFDH.o $(CFLAGS)

# 清理目标
clean:
	if exist ttpMain.exe del ttpMain.exe
	if exist generate.exe del generate.exe
	if exist build\ttpMain.o del build\ttpMain.o
	if exist build\FFDH.o del build\FFDH.o
# 清理目标文件
cleanl:
	rm -f $(TARGET) $(OBJS)
