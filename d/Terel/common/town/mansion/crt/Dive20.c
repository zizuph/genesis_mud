#define DOWN_ROOM	MANSION + "crt/Dive21"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive18","northeast","@@try_hor"); \
    add_exit(MANSION + "crt/Dive21","down","@@try_down"); 

#include "Dive.h"

