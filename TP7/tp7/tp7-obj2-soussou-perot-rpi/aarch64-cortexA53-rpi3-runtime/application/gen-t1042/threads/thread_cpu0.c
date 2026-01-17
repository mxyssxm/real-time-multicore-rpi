#include <librpi3/stdio.h>   // snprintf
#include <librpi3/svc.h>     // get_cpuid, console_puts

#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

#include "../nodes/scheduler.h"   // ton scheduler Heptagon

/* État interne du scheduler (comme dans main.c de la simu) */
static Scheduler__main_mem sched_mem;
static Scheduler__main_out sched_out;

/*************** global init *****************/
void global_init(void)
{
    // init Heptagon
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
        // 1. Un pas de scheduler (comme dans ton main.c PC)
        Scheduler__main_step(&sched_out, &sched_mem);
        Scheduler_data__scheduler_state s = sched_out.s;

        // 2. Construire la ligne "Cycle N : [CPU 0: ...] [CPU 1: ...] [CPU 2: ...]"
        int n = snprintf(buf, sizeof(buf),
                         "[Cycle %d] ", step);

        for (int cpu = 0; cpu < 3; cpu++) {    // 3 CPU
            int running = -1;

            for (int t = 0; t < 5; t++) {      // 5 tâches
                if (s.cpu[t] == cpu &&
                    s.tasks[t].status == Scheduler_data__Running) {
                    running = t;
                }
            }

            if (running == -1) {
                n += snprintf(buf + n, sizeof(buf) - n,
                              "[CPU %d : rien] ", cpu);
            } else {
                n += snprintf(buf + n, sizeof(buf) - n,
                              "[CPU %d : tache %d] ", cpu, running);
            }
        }

        n += snprintf(buf + n, sizeof(buf) - n, "\n");

        // 3. Afficher sur la console série de la RPi
        console_puts(cpuid, buf);

        step++;

        // Petite pause si tu veux ralentir l'affichage (optionnel)
        for (volatile int d = 0; d < 1000000; d++);
    }
}
