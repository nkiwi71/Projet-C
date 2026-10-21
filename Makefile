# Build configuration for the SVG shape-list application.
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -fstack-protector
EXEC = projet_svg

SRCS = main.c shapes.c list.c actions.c modify.c export.c
OBJS = $(SRCS:.c=.o)

# Compile and link the application.
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Compile one source file into an object file.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Alias for the default build target.
build: all

# Remove generated object files and the executable.
clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	make clean
	make build
	./$(EXEC)