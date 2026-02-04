#define UP_ROOM		MANSION + "crt/level4"
#define DOWN_ROOM	MANSION + "crt/Dive6"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive2","east","@@try_hor"); \
    add_exit(MANSION + "crt/level4","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive6","down","@@try_down");

#include "Dive.h"

