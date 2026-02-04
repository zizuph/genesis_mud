
#define DOWN_ROOM (MANSION + "crt/Dive12")

#define CREATEADD \
    add_exit(MANSION + "crt/Dive12","down","@@try_down"); \
    add_exit(MANSION + "crt/Dive4","northwest","@@try_hor"); 

#include "Dive.h"

