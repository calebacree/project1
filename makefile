# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executable names
TARGETS = oss user

# Default target that builds all executables
all: $(TARGETS)

# Rule to build oss executable
oss: oss.c
	$(CC) $(CFLAGS) -o oss oss.c

# Rule to build user executable
user: user.c
	$(CC) $(CFLAGS) -o user user.c

# Clean target to remove all compiled files
clean:
	rm -f $(TARGETS)
