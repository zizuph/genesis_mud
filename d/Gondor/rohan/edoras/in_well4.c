#define UP_ROOM		EDORAS_DIR + "in_well3"
#define DOWN_ROOM   EDORAS_DIR + "in_well5"

#define CREATEADD \
    add_exit(EDORAS_DIR + "in_well3","up","@@try_up"); \
    add_exit(EDORAS_DIR + "in_well5","down","@@try_down");

#include "well.h"
