#include <stdio.h>
#include "scheduler.h"
#include "scheduler_data.h"

void print_scheduler_state(Scheduler_data__scheduler_state s) {
    printf("\nTime = %d\n", s.current_date);

    for (int i = 0; i < Scheduler_data__ntasks; i++) {
        const char *name =
            (s.tasks[i].status == Scheduler_data__Running) ? "RUN" :
            (s.tasks[i].status == Scheduler_data__Ready)   ? "READY" :
                                                             "WAIT";

        printf("Task %d : %-5s  left=%d  deadline=%d\n",
               i,
               name,
               s.tasks[i].left,
               s.tasks[i].current_deadline);
    }
}
