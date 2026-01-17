#include <librpi3/stdio.h>   // snprintf
#include <librpi3/svc.h>     // get_cpuid, console_puts

#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

#include "../nodes/scheduler.h"   // Scheduler__main_* et Scheduler_data__scheduler_state

/* État interne du scheduler Heptagon (comme dans main.c de la simu OBJ1) */
static Scheduler__main_mem sched_mem;
static Scheduler__main_out sched_out;

/*************** global init *****************/
void global_init(void)
{
    // Initialisation de l'état du scheduler (mono-CPU pour l'objectif 1)
    Scheduler__main_reset(&sched_mem);
}

/*************** CPU 0 THREAD ****************/
SECTION_ATTR(".text.cpu0")
void mif_entry_point_cpu0(void)
{
    char buf[256];
    uint32_t cpuid = get_cpuid();
    int step = 0;

    while (1) {
        // 1) Un pas de scheduler (équivalent à Scheduler__main_step dans la simu)
        Scheduler__main_step(&sched_out, &sched_mem);
        Scheduler_data__scheduler_state s = sched_out.s;

        // 2) Chercher la tâche en cours d'exécution (status == Running)
        int running = -1;

        // On suppose 5 tâches (0..4) comme dans l'énoncé
        for (int t = 0; t < 5; t++) {
            if (s.tasks[t].status == Scheduler_data__Running) {
                running = t;
                // si plusieurs étaient Running, on pourrait en prendre une,
                // mais en pratique pour l'objectif 1 il devrait y en avoir au plus une
            }
        }

        // 3) Construire une ligne du type :
        //    [Cycle N] tache en cours : tache X / rien
        if (running == -1) {
            snprintf(buf, sizeof(buf),
                     "[Cycle %d] tache en cours : rien\n", step);
        } else {
            snprintf(buf, sizeof(buf),
                     "[Cycle %d] tache en cours : tache %d\n",
                     step, running);
        }

        // 4) Afficher sur la console série de la Raspberry Pi
        console_puts(cpuid, buf);

        step++;

        // Petite attente (busy-wait) pour ne pas flooder la sortie
        for (volatile int d = 0; d < 1000000; d++) {
            // noop
        }
    }
}
