#include <librpi3/stdio.h>
#include <librpi3/svc.h>

#include "api_lopht.h"
#include "syncvars.h"
#include "variables.h"

#include "../../nodes/scheduler.h"
#include "../../nodes/scheduler_data.h"

/*
 * Thread exécuté sur le CPU 1
 */
SECTION_ATTR(".text.cpu1")
void mif_entry_point_cpu1(void)
{
    uint32_t cpuid = get_cpuid();
    (void)cpuid; // pour éviter un warning si on ne l’utilise pas

    while (1) {
        // Attend que le CPU0 ait fini son "pas" de scheduler
        WAIT_CPU(loc_pc_0, 1);

        // Indique qu’on est passé par ici
        UPDATE_CPU(loc_pc_1, 2);

        // Attend que CPU0 termine le cycle
        WAIT_END(loc_pc_0);
    }
}
