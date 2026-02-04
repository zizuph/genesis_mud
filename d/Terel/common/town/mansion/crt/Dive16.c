#define DOWN_ROOM	MANSION + "crt/Dive18"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive14","west","@@try_hor"); \
    add_exit(MANSION + "crt/Dive18","down","@@try_down"); 

#include "Dive.h"

