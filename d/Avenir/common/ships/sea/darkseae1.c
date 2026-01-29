// Sea in the underground ocean.
//   -Cirion, 1997
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea around is eerie and silent. From "
            +"above you see the pale gloaming of the source "
            +"light. To the west, you seem to be "
            +"close to a large island covered in vegetation.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
