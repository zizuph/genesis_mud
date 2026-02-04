#define DOWN_ROOM	MANSION + "crt/Dive17"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive12","south","@@try_hor"); \
    add_exit(MANSION + "crt/Dive16","east","@@try_hor"); \
    add_exit(MANSION + "crt/Dive17","down","@@try_down"); 

#include "Dive.h"

