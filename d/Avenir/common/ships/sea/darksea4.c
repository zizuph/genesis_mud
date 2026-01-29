// Sea in the underground ocean.
//   -Ilyian, 1995
inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("dark sea");
    set_long("The dark sea around is eerie and silent. Small "
            +"murky ripples form around, signifing some "
            +"strange and enigmatic force.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

}
