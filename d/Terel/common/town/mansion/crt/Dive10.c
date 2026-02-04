#define UP_ROOM		MANSION + "crt/Dive9"
#define DOWN_ROOM	MANSION + "crt/Dive11"

#define CREATEADD \
    add_exit(MANSION + "crt/Dive9","up","@@try_up"); \
    add_exit(MANSION + "crt/Dive11","down","@@try_down");

#include "Dive.h"

