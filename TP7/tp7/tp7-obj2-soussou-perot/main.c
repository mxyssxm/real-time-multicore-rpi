#include <stdio.h>
#include "scheduler_c/scheduler.h"

int main() {
    Scheduler__main_mem mem;
    Scheduler__main_out out;
    Scheduler__main_reset(&mem);

    int step = 0;
    while (1) {
        printf("\n[Cycle %d] Appuyez sur Entrée...\n", step);
        getchar();

        Scheduler__main_step(&out, &mem);
        Scheduler_data__scheduler_state s = out.s;

        printf("Tâches lancées : ");
        for(int cpu=0; cpu<3; cpu++){   // 3 CPU
            int running = -1;

            // Trouver quelle tâche tourne sur ce CPU
            for(int t=0; t<5; t++){     // 5 tâches
                if(s.cpu[t] == cpu && s.tasks[t].status == Scheduler_data__Running){
                    running = t;
                }
            }

            if(running == -1)
                printf("[CPU %d : rien] ", cpu);
            else
                printf("[CPU %d : tache %d] ", cpu, running);
        }
        printf("\n");

        step++;
    }
}
