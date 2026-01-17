#include <stdio.h>
#include <stdlib.h>
#include "scheduler_simu.h"

int main(){
    srand(time(NULL));
    Scheduler_state st=init_sstate;

    while(1){
        getchar();
        st=scheduler(st);
        print_scheduler_state(st);
    }
    return 0;
}
