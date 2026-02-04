#define UP_ROOM		MANSION + "crt/Dive5"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive13","west","@@try_hor"); \
    add_exit(MANSION + "crt/Dive14","north","@@try_hor"); \
    add_exit(MANSION + "crt/Dive5","up","@@try_up"); 

#include "Dive.h"

