#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_cell();

    add_door_exit("towerisl_lev1_key", TOWERISL_ROOM + "t1_05", "southeast");
}

