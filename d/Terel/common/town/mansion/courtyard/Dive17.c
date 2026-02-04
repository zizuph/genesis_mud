#define UP_ROOM MANSION + "crt/Dive14"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive14","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive15","southwest","@@try_hor"); 

#include "Dive.h"

