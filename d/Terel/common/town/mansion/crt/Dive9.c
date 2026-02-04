#define DOWN_ROOM	MANSION + "crt/Dive10"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive7","north","@@try_hor"); \
    add_exit(MANSION + "crt/Dive10","down","@@try_down");

#include "Dive.h"

