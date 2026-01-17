/* --- Generated the 11/12/2025 at 12:1 --- */
/* --- heptagon compiler, version 1.05.00 (compiled wed. nov. 12 16:58:21 CET 2025) --- */
/* --- Command line: /Users/meyssem/.opam/heptagon-4.14/bin/heptc -target c scheduler_data.ept scheduler.ept externc.epi --- */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "scheduler_types.h"
#include "scheduler_data.h"
typedef struct Scheduler__select_aux_out {
  Scheduler__select_acc acc_o;
} Scheduler__select_aux_out;

void Scheduler__select_aux_step(Scheduler_data__task_status ts,
                                Scheduler_data__task_attributes ta, int cpu,
                                int tid, Scheduler__select_acc acc,
                                Scheduler__select_aux_out* _out);

typedef struct Scheduler__select_one_task_out {
  int selected;
} Scheduler__select_one_task_out;

void Scheduler__select_one_task_step(Scheduler_data__task_status ts[5],
                                     int cpu[5],
                                     Scheduler__select_one_task_out* _out);

typedef struct Scheduler__update_selected_out {
  Scheduler_data__task_status tso;
} Scheduler__update_selected_out;

void Scheduler__update_selected_step(Scheduler_data__task_status ts,
                                     int selected, int tid,
                                     Scheduler__update_selected_out* _out);

typedef struct Scheduler__update_cpu_assign_out {
  int nc;
} Scheduler__update_cpu_assign_out;

void Scheduler__update_cpu_assign_step(int old, int selected, int core,
                                       int tid,
                                       Scheduler__update_cpu_assign_out* _out);

typedef struct Scheduler__schedule_one_out {
  Scheduler_data__task_status ts_o[5];
  int cpu_o[5];
} Scheduler__schedule_one_out;

void Scheduler__schedule_one_step(Scheduler_data__task_status ts[5],
                                  int cpu[5], int core,
                                  Scheduler__schedule_one_out* _out);

typedef struct Scheduler__simulate_out {
  Scheduler_data__task_status o;
} Scheduler__simulate_out;

void Scheduler__simulate_step(Scheduler_data__task_status ts,
                              Scheduler__simulate_out* _out);

typedef struct Scheduler__update_cpu_after_out {
  int nc;
} Scheduler__update_cpu_after_out;

void Scheduler__update_cpu_after_step(Scheduler_data__task_status ts,
                                      int old, int tid,
                                      Scheduler__update_cpu_after_out* _out);

typedef struct Scheduler__start_inst_out {
  Scheduler_data__task_status o;
} Scheduler__start_inst_out;

void Scheduler__start_inst_step(int date, Scheduler_data__task_status ts,
                                Scheduler_data__task_attributes ta, int tid,
                                Scheduler__start_inst_out* _out);

typedef struct Scheduler__scheduler_out {
  Scheduler_data__scheduler_state so;
} Scheduler__scheduler_out;

void Scheduler__scheduler_step(Scheduler_data__scheduler_state si,
                               Scheduler__scheduler_out* _out);

typedef struct Scheduler__main_mem {
  Scheduler_data__scheduler_state st;
} Scheduler__main_mem;

typedef struct Scheduler__main_out {
  Scheduler_data__scheduler_state s;
} Scheduler__main_out;

void Scheduler__main_reset(Scheduler__main_mem* self);

void Scheduler__main_step(Scheduler__main_out* _out,
                          Scheduler__main_mem* self);

#endif // SCHEDULER_H
