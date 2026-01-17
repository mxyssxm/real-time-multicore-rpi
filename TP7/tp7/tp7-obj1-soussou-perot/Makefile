# Nom de l'exécutable
EXEC = simu_rm

# Fichiers Heptagon
EPT_FILES = scheduler_data.ept scheduler.ept externc.epi

# Compilateur Heptagon -> C
HEPTC = heptc -target c

# Compilateur C
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Répertoire où heptc génère le C
GEN_DIR = _build/C
GEN_C   = $(GEN_DIR)/scheduler.c

all: $(EXEC)

# Génération du code C à partir des fichiers Heptagon
$(GEN_C): $(EPT_FILES)
	$(HEPTC) $(EPT_FILES)

# Compilation finale
$(EXEC): $(GEN_C) externc.c main.c
	$(CC) $(CFLAGS) -I$(GEN_DIR) $(GEN_C) externc.c main.c -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(EXEC) _build *.o
