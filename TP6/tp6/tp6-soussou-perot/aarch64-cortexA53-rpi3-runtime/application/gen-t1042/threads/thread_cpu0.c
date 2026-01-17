#include <librpi3/stdio.h>   // snprintf
#include <librpi3/svc.h>     // get_cpuid, console_puts

#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

/*************** global init *****************/
void global_init(void)
{
    x = 0;
    y = 0;
    u = 0;
    z = 123;

    loc_pc_0 = -1;
    loc_pc_1 = -1;
}

/*************** CPU 0 THREAD ****************/
SECTION_ATTR(".text.cpu0")
void mif_entry_point_cpu0(void)
{
    char buf[64];
    uint32_t cpuid = get_cpuid();

    while (1) {

        snprintf(buf, 63, "RPI://=========cycle start============\n");
        console_puts(cpuid, buf);

        g_step(z, &y);

        WAIT_CPU(loc_pc_1, 1);

        h_step(x, y, &z);
        UPDATE_CPU(loc_pc_0, 1);

        WAIT_CPU(loc_pc_1, 2);

        loc_pc_1 = -1;
        UPDATE_CPU(loc_pc_0, -1);
    }
}
