/* --- Generated the 11/12/2025 at 12:1 --- */
/* --- heptagon compiler, version 1.05.00 (compiled wed. nov. 12 16:58:21 CET 2025) --- */
/* --- Command line: /Users/meyssem/.opam/heptagon-4.14/bin/heptc -target c scheduler_data.ept scheduler.ept externc.epi --- */

#ifndef SCHEDULER_TYPES_H
#define SCHEDULER_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
#include "scheduler_data_types.h"
typedef struct Scheduler__select_acc {
  int tid;
  int dline;
} Scheduler__select_acc;

#endif // SCHEDULER_TYPES_H
