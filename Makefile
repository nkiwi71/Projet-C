# Définition du compilateur et des options
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g

# Nom de l'exécutable final
TARGET = projet_svg

# Liste des fichiers sources
SRCS = main.c

# Fichiers objets générés
OBJS = $(SRCS:.c=.o)

# Règle pour compiler le projet
build: $(TARGET)

# Édition des liens
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation des fichiers .c en .o
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer le projet
clean:
    rm -f $(OBJS) $(TARGET)