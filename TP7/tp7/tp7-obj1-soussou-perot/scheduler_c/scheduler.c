/* --- Generated the 28/11/2025 at 13:51 --- */
/* --- heptagon compiler, version 1.05.00 (compiled wed. nov. 12 16:58:21 CET 2025) --- */
/* --- Command line: /Users/meyssem/.opam/heptagon-4.14/bin/heptc -target c scheduler_data.ept scheduler.ept externc.epi --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scheduler.h"

void Scheduler__select_aux_step(Scheduler_data__task_status ts,
                                Scheduler_data__task_attributes ta, int tid,
                                Scheduler__select_acc acc,
                                Scheduler__select_aux_out* _out) {
  
  Scheduler__select_acc v_3;
  int v_2;
  int v_1;
  int v;
  v = (ts.status==Scheduler_data__Ready);
  v_1 = (ta.period<acc.speriod);
  v_3.tid = tid;
  v_3.speriod = ta.period;
  v_2 = (v&&v_1);
  if (v_2) {
    _out->acc_o = v_3;
  } else {
    _out->acc_o = acc;
  };;
}

void Scheduler__select_one_task_step(Scheduler_data__task_status ts[2],
                                     Scheduler__select_one_task_out* _out) {
  Scheduler__select_aux_out Scheduler__select_aux_out_st;
  
  Scheduler__select_acc v;
  Scheduler__select_acc tmp;
  v.speriod = 2147483647;
  v.tid = 2;
  tmp = v;
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__select_aux_step(ts[i], Scheduler_data__tasks[i], i, tmp,
                                 &Scheduler__select_aux_out_st);
      tmp = Scheduler__select_aux_out_st.acc_o;
    }
  };
  _out->selected = tmp.tid;;
}

void Scheduler__update_selected_step(Scheduler_data__task_status ts,
                                     int selected, int tid,
                                     Scheduler__update_selected_out* _out) {
  
  Scheduler_data__task_status v_4;
  int v;
  v = (tid==selected);
  v_4.status = Scheduler_data__Running;
  v_4.current_deadline = ts.current_deadline;
  v_4.left = ts.left;
  if (v) {
    _out->tso = v_4;
  } else {
    _out->tso = ts;
  };;
}

void Scheduler__rate_monotonic_step(Scheduler_data__task_status ts[2],
                                    Scheduler__rate_monotonic_out* _out) {
  Scheduler__update_selected_out Scheduler__update_selected_out_st;
  Scheduler__select_one_task_out Scheduler__select_one_task_out_st;
  
  int v[2];
  int selected;
  Scheduler__select_one_task_step(ts, &Scheduler__select_one_task_out_st);
  selected = Scheduler__select_one_task_out_st.selected;
  {
    int i_5;
    for (i_5 = 0; i_5 < Scheduler_data__ntasks; ++i_5) {
      v[i_5] = selected;
    }
  };
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__update_selected_step(ts[i], v[i], i,
                                      &Scheduler__update_selected_out_st);
      _out->tso[i] = Scheduler__update_selected_out_st.tso;
    }
  };;
}

void Scheduler__start_inst_step(int current_date,
                                Scheduler_data__task_status tsi,
                                Scheduler_data__task_attributes ta,
                                Scheduler__start_inst_out* _out) {
  
  Scheduler_data__task_status v_8;
  int v_7;
  int v_6;
  int v_5;
  int v;
  int diff;
  int k;
  int c;
  v_7 = (current_date+ta.deadline);
  v = (current_date>=ta.first_start);
  diff = (current_date-ta.first_start);
  k = (diff/ta.period);
  v_5 = (k*ta.period);
  v_8.status = Scheduler_data__Ready;
  v_8.current_deadline = v_7;
  v_8.left = ta.capacity;
  v_6 = (diff==v_5);
  c = (v&&v_6);
  if (c) {
    _out->tso = v_8;
  } else {
    _out->tso = tsi;
  };;
}

void Scheduler__check_deadline_step(int current_date,
                                    Scheduler_data__task_status tsi, int tid,
                                    Scheduler__check_deadline_out* _out) {
  
  Scheduler_data__task_status v_13;
  int v_12;
  int v_11;
  int v_10;
  int v_9;
  int v;
  v_11 = (tsi.left>0);
  v_9 = (tsi.current_deadline==current_date);
  v = (tsi.status==Scheduler_data__Ready);
  v_10 = (v&&v_9);
  v_12 = (v_10&&v_11);
  v_13.status = Scheduler_data__Waiting;
  v_13.current_deadline = tsi.current_deadline;
  v_13.left = tsi.left;
  if (v_12) {
    _out->tso = v_13;
  } else {
    _out->tso = tsi;
  };;
}

void Scheduler__simulate_step(Scheduler_data__task_status tsi,
                              Scheduler__simulate_out* _out) {
  
  Scheduler_data__task_status v_18;
  Scheduler_data__task_status v_17;
  int v_16;
  Scheduler_data__task_status v_15;
  int v_14;
  int v;
  v_16 = (tsi.left-1);
  v_14 = (tsi.left<=1);
  v = (tsi.status==Scheduler_data__Running);
  v_17.status = Scheduler_data__Ready;
  v_17.current_deadline = tsi.current_deadline;
  v_17.left = v_16;
  v_15.status = Scheduler_data__Waiting;
  v_15.current_deadline = tsi.current_deadline;
  v_15.left = 0;
  if (v_14) {
    v_18 = v_15;
  } else {
    v_18 = v_17;
  };
  if (v) {
    _out->o = v_18;
  } else {
    _out->o = tsi;
  };;
}

void Scheduler__scheduler_step(Scheduler_data__scheduler_state si,
                               Scheduler__scheduler_out* _out) {
  Scheduler__start_inst_out Scheduler__start_inst_out_st;
  Scheduler__check_deadline_out Scheduler__check_deadline_out_st;
  Scheduler__simulate_out Scheduler__simulate_out_st;
  Scheduler__rate_monotonic_out Scheduler__rate_monotonic_out_st;
  
  int v_19[2];
  int v[2];
  int new_date;
  Scheduler_data__task_status tmp1[2];
  Scheduler_data__task_status tmp2[2];
  Scheduler_data__task_status tmp3[2];
  Scheduler_data__task_status fin[2];
  new_date = (si.current_date+1);
  {
    int i_4;
    for (i_4 = 0; i_4 < Scheduler_data__ntasks; ++i_4) {
      Scheduler__simulate_step(si.tasks[i_4], &Scheduler__simulate_out_st);
      tmp1[i_4] = Scheduler__simulate_out_st.o;
    }
  };
  {
    int i_3;
    for (i_3 = 0; i_3 < Scheduler_data__ntasks; ++i_3) {
      v_19[i_3] = new_date;
    }
  };
  {
    int i_2;
    for (i_2 = 0; i_2 < Scheduler_data__ntasks; ++i_2) {
      v[i_2] = new_date;
    }
  };
  {
    int i_1;
    for (i_1 = 0; i_1 < Scheduler_data__ntasks; ++i_1) {
      Scheduler__check_deadline_step(v[i_1], tmp1[i_1], i_1,
                                     &Scheduler__check_deadline_out_st);
      tmp2[i_1] = Scheduler__check_deadline_out_st.tso;
    }
  };
  {
    int i;
    for (i = 0; i < Scheduler_data__ntasks; ++i) {
      Scheduler__start_inst_step(v_19[i], tmp2[i], Scheduler_data__tasks[i],
                                 &Scheduler__start_inst_out_st);
      tmp3[i] = Scheduler__start_inst_out_st.tso;
    }
  };
  Scheduler__rate_monotonic_step(tmp3, &Scheduler__rate_monotonic_out_st);
  {
    int _1;
    for (_1 = 0; _1 < 2; ++_1) {
      fin[_1] = Scheduler__rate_monotonic_out_st.tso[_1];
    }
  };
  _out->so.current_date = new_date;
  {
    int _2;
    for (_2 = 0; _2 < 2; ++_2) {
      _out->so.tasks[_2] = fin[_2];
    }
  };;
}

void Scheduler__main_reset(Scheduler__main_mem* self) {
  {
    int _3;
    for (_3 = 0; _3 < 2; ++_3) {
      self->st.tasks[_3].left = 0;
      self->st.tasks[_3].current_deadline = 0;
      self->st.tasks[_3].status = Scheduler_data__Waiting;
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

