/* --- Generated the 3/12/2025 at 14:18 --- */
/* --- heptagon compiler, version 1.05.00 (compiled wed. nov. 12 16:58:21 CET 2025) --- */
/* --- Command line: /Users/meyssem/.opam/heptagon-4.14/bin/heptc -target c scheduler_data.ept scheduler.ept externc.epi --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scheduler.h"

void Scheduler__select_aux_step(Scheduler_data__task_status ts,
                                Scheduler_data__task_attributes ta, int cpu,
                                int tid, Scheduler__select_acc acc,
                                Scheduler__select_aux_out* _out) {
  
  Scheduler__select_acc v_5;
  int v_4;
  int v_3;
  int v_2;
  int v_1;
  int v;
  v = (ts.status==Scheduler_data__Ready);
  v_3 = (ta.period<acc.speriod);
  v_5.tid = tid;
  v_5.speriod = ta.period;
  v_1 = (cpu==Scheduler_data__nocpu);
  v_2 = (v&&v_1);
  v_4 = (v_2&&v_3);
  if (v_4) {
    _out->acc_o = v_5;
  } else {
    _out->acc_o = acc;
  };;
}

void Scheduler__select_one_task_step(Scheduler_data__task_status ts[5],
                                     int cpu[5],
                                     Scheduler__select_one_task_out* _out) {
  Scheduler__select_aux_out Scheduler__select_aux_out_st;
  
  Scheduler__select_acc v;
  Scheduler__select_acc tmp;
  v.speriod = 2147483647;
  v.tid = 5;
  tmp = v;
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__select_aux_step(ts[i], Scheduler_data__tasks[i], cpu[i], i,
                                 tmp, &Scheduler__select_aux_out_st);
      tmp = Scheduler__select_aux_out_st.acc_o;
    }
  };
  _out->selected = tmp.tid;;
}

void Scheduler__update_selected_step(Scheduler_data__task_status ts,
                                     int selected, int tid,
                                     Scheduler__update_selected_out* _out) {
  
  Scheduler_data__task_status v_6;
  int v;
  v = (tid==selected);
  v_6.status = Scheduler_data__Running;
  v_6.current_deadline = ts.current_deadline;
  v_6.left = ts.left;
  if (v) {
    _out->tso = v_6;
  } else {
    _out->tso = ts;
  };;
}

void Scheduler__update_cpu_assign_step(int old, int selected, int core,
                                       int tid,
                                       Scheduler__update_cpu_assign_out* _out) {
  
  int v;
  v = (tid==selected);
  if (v) {
    _out->nc = core;
  } else {
    _out->nc = old;
  };;
}

void Scheduler__schedule_one_step(Scheduler_data__task_status ts[5],
                                  int cpu[5], int core,
                                  Scheduler__schedule_one_out* _out) {
  Scheduler__update_selected_out Scheduler__update_selected_out_st;
  Scheduler__select_one_task_out Scheduler__select_one_task_out_st;
  Scheduler__update_cpu_assign_out Scheduler__update_cpu_assign_out_st;
  
  int v_8[5];
  int v_7[5];
  int v[5];
  int sel;
  Scheduler__select_one_task_step(ts, cpu, &Scheduler__select_one_task_out_st);
  sel = Scheduler__select_one_task_out_st.selected;
  {
    int i_7;
    for (i_7 = 0; i_7 < Scheduler_data__ntasks; ++i_7) {
      v_8[i_7] = core;
    }
  };
  {
    int i_6;
    for (i_6 = 0; i_6 < Scheduler_data__ntasks; ++i_6) {
      v_7[i_6] = sel;
    }
  };
  {
    int i_5;
    for (i_5 = 0; i_5 < Scheduler_data__ntasks; ++i_5) {
      Scheduler__update_cpu_assign_step(cpu[i_5], v_7[i_5], v_8[i_5], i_5,
                                        &Scheduler__update_cpu_assign_out_st);
      _out->cpu_o[i_5] = Scheduler__update_cpu_assign_out_st.nc;
    }
  };
  {
    int i_4;
    for (i_4 = 0; i_4 < Scheduler_data__ntasks; ++i_4) {
      v[i_4] = sel;
    }
  };
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__update_selected_step(ts[i], v[i], i,
                                      &Scheduler__update_selected_out_st);
      _out->ts_o[i] = Scheduler__update_selected_out_st.tso;
    }
  };;
}

void Scheduler__simulate_step(Scheduler_data__task_status ts,
                              Scheduler__simulate_out* _out) {
  
  Scheduler_data__task_status v_13;
  Scheduler_data__task_status v_12;
  Scheduler_data__task_status v_11;
  int v_10;
  int v_9;
  int v;
  v_10 = (ts.left-1);
  v_9 = (ts.left>1);
  v = (ts.status==Scheduler_data__Running);
  v_12.status = Scheduler_data__Waiting;
  v_12.current_deadline = ts.current_deadline;
  v_12.left = 0;
  v_11.status = Scheduler_data__Running;
  v_11.current_deadline = ts.current_deadline;
  v_11.left = v_10;
  if (v_9) {
    v_13 = v_11;
  } else {
    v_13 = v_12;
  };
  if (v) {
    _out->o = v_13;
  } else {
    _out->o = ts;
  };;
}

void Scheduler__update_cpu_after_step(Scheduler_data__task_status ts,
                                      int old, int tid,
                                      Scheduler__update_cpu_after_out* _out) {
  
  int v;
  v = (ts.status==Scheduler_data__Running);
  if (v) {
    _out->nc = old;
  } else {
    _out->nc = -1;
  };;
}

void Scheduler__start_inst_step(int date, Scheduler_data__task_status ts,
                                Scheduler_data__task_attributes ta, int tid,
                                Scheduler__start_inst_out* _out) {
  
  Scheduler_data__task_status v_19;
  int v_18;
  int v_17;
  int v_16;
  int v_15;
  int v_14;
  int v;
  int diff;
  int k;
  int c;
  v_18 = (date+ta.deadline);
  v_16 = (ts.status==Scheduler_data__Waiting);
  v = (date>=ta.first_start);
  diff = (date-ta.first_start);
  k = (diff/ta.period);
  v_14 = (k*ta.period);
  v_19.status = Scheduler_data__Ready;
  v_19.current_deadline = v_18;
  v_19.left = ta.capacity;
  v_15 = (diff==v_14);
  c = (v&&v_15);
  v_17 = (c&&v_16);
  if (v_17) {
    _out->o = v_19;
  } else {
    _out->o = ts;
  };;
}

void Scheduler__scheduler_step(Scheduler_data__scheduler_state si,
                               Scheduler__scheduler_out* _out) {
  Scheduler__start_inst_out Scheduler__start_inst_out_st;
  Scheduler__update_cpu_after_out Scheduler__update_cpu_after_out_st;
  Scheduler__simulate_out Scheduler__simulate_out_st;
  Scheduler__schedule_one_out Scheduler__schedule_one_out_st;
  
  int v[5];
  int d;
  Scheduler_data__task_status t_sim[5];
  Scheduler_data__task_status t_new[5];
  Scheduler_data__task_status t_c0[5];
  Scheduler_data__task_status t_c1[5];
  Scheduler_data__task_status t_c2[5];
  int cpu_after[5];
  int cpu0[5];
  int cpu1[5];
  int cpu2[5];
  d = (si.current_date+1);
  {
    int i_3;
    for (i_3 = 0; i_3 < Scheduler_data__ntasks; ++i_3) {
      v[i_3] = d;
    }
  };
  {
    int i_2;
    for (i_2 = 0; i_2 < Scheduler_data__ntasks; ++i_2) {
      Scheduler__simulate_step(si.tasks[i_2], &Scheduler__simulate_out_st);
      t_sim[i_2] = Scheduler__simulate_out_st.o;
    }
  };
  {
    int i_1;
    for (i_1 = 0; i_1 < Scheduler_data__ntasks; ++i_1) {
      Scheduler__start_inst_step(v[i_1], t_sim[i_1],
                                 Scheduler_data__tasks[i_1], i_1,
                                 &Scheduler__start_inst_out_st);
      t_new[i_1] = Scheduler__start_inst_out_st.o;
    }
  };
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__update_cpu_after_step(t_sim[i], si.cpu[i], i,
                                       &Scheduler__update_cpu_after_out_st);
      cpu_after[i] = Scheduler__update_cpu_after_out_st.nc;
    }
  };
  Scheduler__schedule_one_step(t_new, cpu_after, 0,
                               &Scheduler__schedule_one_out_st);
  {
    int _1;
    for (_1 = 0; _1 < 5; ++_1) {
      t_c0[_1] = Scheduler__schedule_one_out_st.ts_o[_1];
    }
  };
  {
    int _2;
    for (_2 = 0; _2 < 5; ++_2) {
      cpu0[_2] = Scheduler__schedule_one_out_st.cpu_o[_2];
    }
  };
  Scheduler__schedule_one_step(t_c0, cpu0, 1, &Scheduler__schedule_one_out_st);
  {
    int _3;
    for (_3 = 0; _3 < 5; ++_3) {
      t_c1[_3] = Scheduler__schedule_one_out_st.ts_o[_3];
    }
  };
  {
    int _4;
    for (_4 = 0; _4 < 5; ++_4) {
      cpu1[_4] = Scheduler__schedule_one_out_st.cpu_o[_4];
    }
  };
  Scheduler__schedule_one_step(t_c1, cpu1, 2, &Scheduler__schedule_one_out_st);
  {
    int _5;
    for (_5 = 0; _5 < 5; ++_5) {
      t_c2[_5] = Scheduler__schedule_one_out_st.ts_o[_5];
    }
  };
  {
    int _6;
    for (_6 = 0; _6 < 5; ++_6) {
      cpu2[_6] = Scheduler__schedule_one_out_st.cpu_o[_6];
    }
  };
  _out->so.current_date = d;
  {
    int _8;
    for (_8 = 0; _8 < 5; ++_8) {
      _out->so.cpu[_8] = cpu2[_8];
    }
  };
  {
    int _7;
    for (_7 = 0; _7 < 5; ++_7) {
      _out->so.tasks[_7] = t_c2[_7];
    }
  };;
}

void Scheduler__main_reset(Scheduler__main_mem* self) {
  {
    int _10;
    for (_10 = 0; _10 < 5; ++_10) {
      self->st.tasks[_10].left = 0;
      self->st.tasks[_10].current_deadline = 0;
      self->st.tasks[_10].status = Scheduler_data__Waiting;
    }
  };
  {
    int _9;
    for (_9 = 0; _9 < 5; ++_9) {
      self->st.cpu[_9] = -1;
    }
  };
  self->st.current_date = -1;
}

void Scheduler__main_step(Scheduler__main_out* _out,
                          Scheduler__main_mem* self) {
  Scheduler__scheduler_out Scheduler__scheduler_out_st;
  
  Scheduler_data__scheduler_state v;
  _out->s = self->st;
  Scheduler__scheduler_step(self->st, &Scheduler__scheduler_out_st);
  v = Scheduler__scheduler_out_st.so;
  self->st = v;;
}

