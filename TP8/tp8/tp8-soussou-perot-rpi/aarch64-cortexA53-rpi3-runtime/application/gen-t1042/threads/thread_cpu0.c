#include <librpi3/stdio.h>
#include <librpi3/svc.h>

#include "api_lopht.h"
#include "syncvars.h"
#include "variables.h"

#include "../../nodes/scheduler.h"
#include "../../nodes/scheduler_data.h"

/*
 * Initialisation globale appelée AVANT le démarrage des threads CPU.
 * On réinitialise l’état du scheduler Heptagon.
 */
void global_init(void)
{
    // Initialise les compteurs de synchro
    loc_pc_0 = -1;
    loc_pc_1 = -1;
    // loc_pc_2 existe peut-être, mais on ne l’utilise pas en bi-coeur.

    // Reset du scheduler Heptagon (node main)
    Scheduler__main_reset(&scheduler_mem);
}

/*
 * Thread exécuté sur le CPU 0
 */
SECTION_ATTR(".text.cpu0")
void mif_entry_point_cpu0(void)
{
    char buf[128];
    uint32_t cpuid = get_cpuid();

    while (1) {
        // Un pas de scheduler Heptagon : s = main()
        Scheduler__main_step(&scheduler_out, &scheduler_mem);
        Scheduler_data__scheduler_state s = scheduler_out.s;

        // Affichage du cycle courant
        snprintf(buf, sizeof(buf), "\n===== Cycle %d =====\n", s.current_date);
        console_puts(cpuid, buf);

        // Affichage des tâches lancées sur chaque CPU (0 et 1)
        for (int cpu = 0; cpu < 2; cpu++) {   // bi-coeur : 0 et 1
            int running = -1;

            for (int t = 0; t < Scheduler_data__ntasks; t++) {
                if (s.cpu[t] == cpu &&
                    s.tasks[t].status == Scheduler_data__Running) {
                    running = t;
                }
            }

            if (running == -1) {
                snprintf(buf, sizeof(buf),
                         "[CPU %d : rien]\n", cpu);
            } else {
                snprintf(buf, sizeof(buf),
                         "[CPU %d : tache %d]\n", cpu, running);
            }
            console_puts(cpuid, buf);
        }

        // Synchronisation simple avec le CPU 1
        UPDATE_CPU(loc_pc_0, 1);   // CPU0 signale qu’il a fini le cycle
        WAIT_CPU(loc_pc_1, 2);     // attend que CPU1 ait synchronisé loc_pc_1
        loc_pc_1 = -1;             // remet à zéro l’état du CPU1
        UPDATE_CPU(loc_pc_0, -1);  // fin de cycle pour CPU0
    }
}
