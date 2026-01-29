#include "../defs.h"

inherit T1_IN_BASE;

nomask void
create_t1_room()
{
    add_hallway();

    add_exit("t1_08", "southwest");
    add_exit("t1_02", "northeast");
    add_door_exit("towerisl_lev1_key", TOWERISL_ROOM + "t1_01", "northwest");
}
