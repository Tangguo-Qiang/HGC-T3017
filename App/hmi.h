#ifndef __HMI_H
#define __HMI_H

#include "system.h"

extern byte TypeSetState;
extern byte TypeSetDelay;


extern void KeyProcessMainForm(KeyActEnum key);
extern void KeyProcessFaultForm(KeyActEnum key);
extern void KeyProcessDevTypeForm(KeyActEnum key);

#endif
