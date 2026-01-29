#include "defs.h"

inherit PAV_ROOM;

void
create_pav_room()
{
    add_exit("pav3", "east");
    add_exit("pav6", "northwest");
    add_exit("pav8", "southwest");

    add_information_desk();
}
