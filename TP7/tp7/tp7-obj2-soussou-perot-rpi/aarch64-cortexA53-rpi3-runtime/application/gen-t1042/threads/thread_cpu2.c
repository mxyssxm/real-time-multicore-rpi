#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

SECTION_ATTR(".text.cpu2")
void mif_entry_point_cpu2(void)
{
    while (1) {
        // CPU2 ne fait rien dans cette version
    }
}
