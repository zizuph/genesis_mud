#define UP_ROOM MANSION + "crt/Dive13"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive13","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive8","northwest","@@try_hor");  \
    add_exit(MANSION + "crt/Dive17","northeast","@@try_hor"); 

#include "Dive.h"

