/* --- Generated the 11/12/2025 at 12:1 --- */
/* --- heptagon compiler, version 1.05.00 (compiled wed. nov. 12 16:58:21 CET 2025) --- */
/* --- Command line: /Users/meyssem/.opam/heptagon-4.14/bin/heptc -target c scheduler_data.ept scheduler.ept externc.epi --- */

#ifndef SCHEDULER_DATA_TYPES_H
#define SCHEDULER_DATA_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
typedef struct Scheduler_data__task_attributes {
  int period;
  int capacity;
  int deadline;
  int first_start;
} Scheduler_data__task_attributes;

static const int Scheduler_data__ntasks = 5;

static const int Scheduler_data__ncores = 2;

static const Scheduler_data__task_attributes Scheduler_data__tasks[5] = {
{10, 3, 10, 0}, {12, 4, 12, 0}, {20, 5, 20, 0}, {15, 2, 15, 0}, {8, 3, 8, 0}};

static const int Scheduler_data__int_max = 2147483647;

static const int Scheduler_data__nocpu = -1;

typedef enum {
  Scheduler_data__Running,
  Scheduler_data__Ready,
  Scheduler_data__Waiting
} Scheduler_data__task_state;

Scheduler_data__task_state Scheduler_data__task_state_of_string(char* s);

char* string_of_Scheduler_data__task_state(Scheduler_data__task_state x,
                                           char* buf);

typedef struct Scheduler_data__task_status {
  Scheduler_data__task_state status;
  int current_deadline;
  int left;
} Scheduler_data__task_status;

typedef struct Scheduler_data__scheduler_state {
  int current_date;
  int cpu[5];
  Scheduler_data__task_status tasks[5];
} Scheduler_data__scheduler_state;

static const Scheduler_data__scheduler_state Scheduler_data__init_sstate = {
-1,
{Scheduler_data__nocpu, Scheduler_data__nocpu, Scheduler_data__nocpu,
 Scheduler_data__nocpu, Scheduler_data__nocpu},
{{Scheduler_data__Waiting, 0, 0}, {Scheduler_data__Waiting, 0, 0},
 {Scheduler_data__Waiting, 0, 0}, {Scheduler_data__Waiting, 0, 0},
 {Scheduler_data__Waiting, 0, 0}}};

#endif // SCHEDULER_DATA_TYPES_H
