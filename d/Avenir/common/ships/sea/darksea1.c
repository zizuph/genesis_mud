// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea around is eerie and silent. From "
            +"above you see the pale gloaming of the source "
            +"light. To the south, you seem to be "
            +"close to a large island covered with a "
            +"scattering of buildings.\n");
    AI(({"island","islands","bazaar"}),"The island is large, "
            +"and you can barely make out shouting voices "
            +"from it.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
