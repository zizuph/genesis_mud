// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea around is eerie and silent. Far "
            +"to the north you can just make out a "
            +"fog covered island that fills you with a "
            +"sense of dread.\n");
    AI(({"island","islands"}),"All you can make out "
            +"about the island from here is that it "
            +"is covered in fog.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
