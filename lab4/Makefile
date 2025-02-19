# Compiler 
CC = gcc

# Compiler flags
CFLAGS = -c

# Files 
SRC = my_shell.c my_fgets.c exe_cmd.c 
OBJ = my_shell.o my_fgets.o exe_cmd.o 
TARGET = my_shell

# Default target (compiles everything)
all: $(TARGET)

# Compile source files into object files
my_shell.o: my_shell.c my_fgets.h exe_cmd.h
	$(CC) $(CFLAGS) my_shell.c -o my_shell.o

my_fgets.o: my_fgets.c my_fgets.h
	$(CC) $(CFLAGS) my_fgets.c -o my_fgets.o

exe_cmd.o: exe_cmd.c exe_cmd.h
	$(CC) $(CFLAGS) exe_cmd.c -o exe_cmd.o

# Link object files into the final executable
$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Clean up object files
clean:
	rm -f $(OBJ) $(TARGET)
