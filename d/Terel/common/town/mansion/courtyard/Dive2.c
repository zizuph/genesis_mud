#define DOWN_ROOM	MANSION + "crt/Dive7"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive4","east","@@try_hor"); \
    add_exit(MANSION + "crt/Dive1","west","@@try_hor"); \
    add_exit(MANSION + "crt/Dive7","down","@@try_down");

#include "Dive.h"

