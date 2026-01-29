#pragma strict_types

#include "../../defs.h"

inherit (ROOM + "room");

public nomask void
create_udun_room()
{
    set_short("At the end of Cirith Gorgor");

    set_long("The broad paved road leads northwards " +
    "to the Black gate and southwards to the open " +
    "plains of Udun, which approaches slightly " +
    "into the view as the meeting of Ephel Duath " +
    "and Ered Lithui widens.\n");

    add_exit(ROAD + "gor1", "north");
    add_exit(ROAD + "gor3", "south");
}