CC = g++
CFLAGS = -std=c++11 -Wall

# Set target executable name
TARGET = dict

# Source files
SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Compiler command for creating the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

