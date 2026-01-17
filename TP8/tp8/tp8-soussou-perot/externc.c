#include <stdio.h>
#include "scheduler.h"   // généré par heptc

void print_scheduler_state(Scheduler_state s) {
    printf("\nTime = %d\n", s.current_date);
    for(int i=0;i<ntasks;i++) {
        const char* name =
            s.tasks[i].status==Running ? "RUN" :
            s.tasks[i].status==Ready   ? "READY" : "WAIT";
        printf("Task %d : %-5s  left=%d  deadline=%d\n",
               i, name, s.tasks[i].left, s.tasks[i].current_deadline);
    }
}
