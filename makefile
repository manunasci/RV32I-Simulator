
CXX = g++
CXXFLAGS = -std=c++17 - Wall -g
SRCDIR = src 
BINDIR = bin 
EXEC = simulador

SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/
CPU.cpp $(SRCDIR)/memoria.cpp $(SRCDIR)/
Bus.cpp $(SRCDIR)/ IO_Device.cpp

TARGET = $(BINDIR)/$(EXEC).exe 

all: $(BINDIR) $(TARGET)

$(BINDIR):
mkdir -p $(BINDIR)

$(TARGET) : $(SOURCES)
$(CXX) $(CXXFLAGS) $(SOURCES) -O $(TARGET)
@echo "Clean successful!"

run: all
./$(TARGET)

.PHONY: all clean run
