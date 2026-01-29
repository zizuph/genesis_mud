// Sea in the underground ocean.
//   -Cirion, 1997
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("All around is the dark sea. The water is menacing "
       + "and still.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
