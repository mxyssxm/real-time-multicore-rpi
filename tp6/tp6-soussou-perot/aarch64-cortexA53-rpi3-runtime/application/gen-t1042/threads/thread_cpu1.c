#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

/* point d’entrée CPU 1 */
SECTION_ATTR(".text.cpu1")
void mif_entry_point_cpu1(void)
{
    while (1) {
        f_step(&x);
        UPDATE_CPU(loc_pc_1, 1);

        m_step(x, &u);

        WAIT_CPU(loc_pc_0, 1);

        n_step(u, z);
        UPDATE_CPU(loc_pc_1, 2);

        WAIT_END(loc_pc_0);
    }
}
