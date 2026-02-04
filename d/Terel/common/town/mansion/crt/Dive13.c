
#define DOWN_ROOM (MANSION + "crt/Dive15")

#define CREATEADD \
    add_exit(MANSION + "crt/Dive12","east","@@try_hor"); \
    add_exit(MANSION + "crt/Dive15","down","@@try_down"); 

#include "Dive.h"

