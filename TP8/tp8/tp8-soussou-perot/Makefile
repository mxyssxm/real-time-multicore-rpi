EXEC = simu_obj2

EPT_FILES = scheduler_data.ept scheduler.ept externc.epi

HEPTC    = heptc
HEPT_STD = $(shell heptc -where)

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 \
          -I$(HEPT_STD) -I$(HEPT_STD)/c \
          -Ischeduler_c -Ischeduler_data_c

all: $(EXEC)

$(EXEC): $(EPT_FILES) main.c
	$(HEPTC) -target c $(EPT_FILES)
	$(CC) $(CFLAGS) scheduler_c/*.c scheduler_data_c/*.c main.c -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(EXEC) scheduler_c scheduler_data_c externc_c *.epci *.log *.mls



#Après avoir exécuté le make, écrire dans le terminal : "./simu_obj2" ou "make run"