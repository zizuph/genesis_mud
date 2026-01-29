#include "defs.h"

inherit PAV_ROOM;

void
create_pav_room()
{
    add_exit("pav4", "south");
    add_exit("pav7", "northeast");
    add_exit("pav5", "northwest");

    add_information_desk();
}
