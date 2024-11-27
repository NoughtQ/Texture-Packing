CXX = g++
CFLAGS = -g
DEBUGGER = gdb

HEADER = ../scripts/ttpHeader.h
FILES = ../scripts/ttpMain.cpp ../scripts/FFDH.cpp
OBJS = ttpMain.o FFDH.o
TARGET = ttpMain
EXE = ttpMain.exe

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

debug : 
	$(CXX) -o $(TARGET) $(FILES) $(CFLAGS)
	$(DEBUGGER) $(TARGET)

ttpMain.o : $(HEADER)
	$(CXX) -c ../scripts/ttpMain.cpp

FFDH.o : $(HEADER)
	$(CXX) -c ../scripts/FFDH.cpp

clean :
	- del $(EXE) $(OBJS)

cleanl :
	rm -f $(TARGET) $(OBJS)