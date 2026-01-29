#define UP_ROOM	 EDORAS_DIR + "in_well4"
#define DOWN_ROOM   EDORAS_DIR + "in_well6"

#define CREATEADD \
    add_exit(EDORAS_DIR + "in_well4","up","@@try_up"); \
    add_exit(EDORAS_DIR + "in_well6","down","@@try_down");

#include "well.h"
