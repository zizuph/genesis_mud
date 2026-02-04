#define UP_ROOM		MANSION + "crt/Dive7"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive15","southeast","@@try_hor"); \
    add_exit(MANSION + "crt/Dive7","up","@@try_up"); 

#include "Dive.h"

