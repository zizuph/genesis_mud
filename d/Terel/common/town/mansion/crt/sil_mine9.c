#define EXITS \
    add_exit(MANSION + "crt/sil_mine7", "west","@@check_boots");\
    add_exit(MANSION + "crt/sil_mine12", "southwest","@@check_boots");

#define ADDS \
    object amber;

#define RESETADD \
    if (!amber || !present(amber,this_object())) { \
	amber = clone_object(MANSION + "obj/amber"); \
	amber->move(this_object()); \
    }

#include "sil_mine.h"
