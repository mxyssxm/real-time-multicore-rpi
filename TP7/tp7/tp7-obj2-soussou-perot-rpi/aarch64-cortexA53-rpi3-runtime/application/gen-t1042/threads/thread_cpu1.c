#include "api_lopht.h"
#include "syncvars.h"
#include "nodes.h"
#include "variables.h"
#include "threads.h"

SECTION_ATTR(".text.cpu1")
void mif_entry_point_cpu1(void)
{
    while (1) {
        // CPU1 ne fait rien dans cette version
    }
}
