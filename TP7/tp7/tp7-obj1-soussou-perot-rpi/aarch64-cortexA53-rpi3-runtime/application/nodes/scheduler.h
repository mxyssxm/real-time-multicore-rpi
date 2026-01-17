/* --- Generated the 28/11/2025 at 13:51 --- */
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
                                Scheduler_data__task_attributes ta, int tid,
                                Scheduler__select_acc acc,
                                Scheduler__select_aux_out* _out);

typedef struct Scheduler__select_one_task_out {
  int selected;
} Scheduler__select_one_task_out;

void Scheduler__select_one_task_step(Scheduler_data__task_status ts[2],
                                     Scheduler__select_one_task_out* _out);

typedef struct Scheduler__update_selected_out {
  Scheduler_data__task_status tso;
} Scheduler__update_selected_out;

void Scheduler__update_selected_step(Scheduler_data__task_status ts,
                                     int selected, int tid,
                                     Scheduler__update_selected_out* _out);

typedef struct Scheduler__rate_monotonic_out {
  Scheduler_data__task_status tso[2];
} Scheduler__rate_monotonic_out;

void Scheduler__rate_monotonic_step(Scheduler_data__task_status ts[2],
                                    Scheduler__rate_monotonic_out* _out);

typedef struct Scheduler__start_inst_out {
  Scheduler_data__task_status tso;
} Scheduler__start_inst_out;

void Scheduler__start_inst_step(int current_date,
                                Scheduler_data__task_status tsi,
                                Scheduler_data__task_attributes ta,
                                Scheduler__start_inst_out* _out);

typedef struct Scheduler__check_deadline_out {
  Scheduler_data__task_status tso;
} Scheduler__check_deadline_out;

void Scheduler__check_deadline_step(int current_date,
                                    Scheduler_data__task_status tsi, int tid,
                                    Scheduler__check_deadline_out* _out);

typedef struct Scheduler__simulate_out {
  Scheduler_data__task_status o;
} Scheduler__simulate_out;

void Scheduler__simulate_step(Scheduler_data__task_status tsi,
                              Scheduler__simulate_out* _out);

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
