CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRCDIR = src
BINDIR = bin
EXEC = simulador

SOURCES = \
    $(SRCDIR)/main.cpp \
    $(SRCDIR)/CPU.cpp \
    $(SRCDIR)/memoria.cpp \
    $(SRCDIR)/Bus.cpp \
    $(SRCDIR)/IO_Device.cpp

TARGET = $(BINDIR)/$(EXEC).exe

all: $(BINDIR) $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Build successful!"

run: all
	./$(TARGET)

clean:
	rm -rf $(BINDIR)
	@echo "Clean successful!"

.PHONY: all clean run
