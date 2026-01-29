// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea spreads around the boat with "
            +"absolutely nothing in sight, eerie black "
            +"water looming fearfully on each horizon.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
