#define UP_ROOM		MANSION + "crt/Dive16"
#define DOWN_ROOM	MANSION + "crt/Dive19"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive20","southwest","@@try_hor"); \
    add_exit(MANSION + "crt/Dive16","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive19","down","@@try_down");

#include "Dive.h"

