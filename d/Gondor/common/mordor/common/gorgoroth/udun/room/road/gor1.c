#pragma strict_types

#include "../../defs.h"

inherit (ROOM + "room");

public nomask void
create_udun_room() {
    set_short("In the pass of Cirith Gorgor");
    set_long("You are on a broad, paved road leading northwards " +
             "to the Morannon and southwards to the open plains " +
             "of the Udun.\n");
    add_exit(ROAD + "gor2", "south");
}
