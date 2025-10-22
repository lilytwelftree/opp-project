# Makefile for Raylib Cake Game
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 \
  -I/opt/homebrew/opt/raylib/include

# Linker flags for macOS (Homebrew raylib)
LDFLAGS = -L/opt/homebrew/opt/raylib/lib -lraylib \
  -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

# Target executable
TARGET = cake

# Source files
SOURCES = FinalGameWRaylib.cpp \
  Stock.cpp Shop.cpp Order.cpp Cake.cpp Store.cpp \
  Frosting.cpp Sprinkles.cpp Topping.cpp Decorations.cpp Time.cpp

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# # Show help
# help:
# 	@echo "Available targets:"
# 	@echo "  all      - Build the raylib game"
# 	@echo "  clean    - Remove executable"
# 	@echo "  run      - Build and run the game"
# 	@echo "  help     - Show this help message"

# .PHONY: all clean run help
