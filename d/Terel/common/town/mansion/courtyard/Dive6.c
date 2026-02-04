#define UP_ROOM		MANSION + "crt/Dive1"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive7","east","@@try_hor"); \
    add_exit(MANSION + "crt/Dive1","up","@@try_up"); 

#include "Dive.h"

