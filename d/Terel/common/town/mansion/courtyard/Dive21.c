#define UP_ROOM MANSION + "crt/Dive20"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive20","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive22","east","@@try_hor");

#include "Dive.h"

