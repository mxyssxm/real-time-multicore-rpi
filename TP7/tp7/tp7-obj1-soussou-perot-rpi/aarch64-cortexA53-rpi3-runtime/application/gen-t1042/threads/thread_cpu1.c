#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

/* point d’entrée CPU 1 : ici on ne fait rien, tout est piloté par CPU0 */
SECTION_ATTR(".text.cpu1")
void mif_entry_point_cpu1(void)
{
    while (1) {
        // CPU1 idle dans cette version
    }
}
