#define UP_ROOM		MANSION + "crt/Dive2"
#define DOWN_ROOM	MANSION + "crt/Dive8"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive6","west","@@try_hor"); \
    add_exit(MANSION + "crt/Dive3","east","@@try_hor"); \
    add_exit(MANSION + "crt/Dive9","south","@@try_hor"); \
    add_exit(MANSION + "crt/Dive2","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive8","down","@@try_down");

#include "Dive.h"

