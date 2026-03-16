#ifndef __DASGIP_UTILS_V1_H
#define __DASGIP_UTILS_V1_H


#include "main.h"
#include "dasgip_state.h"


#define epsilon 1e-6
int DasgipState_SetPointChanged(const DasgipState *pre,
                               const DasgipState *new,
                              double sp_epsilon);

void print_old_new_values(DasgipState my_new, DasgipState my_old);


void write_vessel_actions(const char *filename, DasgipState *s);

int read_dasgip_state(const char *path, DasgipState *s);

void read_assign_state(const char *file, DasgipState *s);
#endif /* end of file */
