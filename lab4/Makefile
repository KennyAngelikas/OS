# Compiler
CC = gcc

# Compiler flags: compile only
CFLAGS = -c

# Directory for object files
OBJ_DIR = bin

# Source files
SRC = my_shell.c my_fgets.c exe_cmd.c builtin.c tokenizer.c pipe_handler.c

# Automatically generate object file names in the bin/ folder
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = my_shell

# Default target: build the executable
all: $(TARGET)

# Link object files to produce the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Pattern rule: compile .c files to .o files in bin/
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up generated files
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
