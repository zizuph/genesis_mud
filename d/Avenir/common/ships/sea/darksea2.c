// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea around is eerie and silent. "
            +"Far to the south you can make out a "
            +"large island, and to the north you "
            +"can see nothing but the murky black "
            +"water.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
