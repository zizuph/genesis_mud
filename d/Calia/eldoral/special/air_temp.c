#include "defs.h"

inherit "/std/room";

public void
create_room()
{
    set_short("high in the air above Calia");
    set_long("You are high in the air above Calia. Beneath " +
        "you, sparse clouds cover parts of the countryside, " +
        "but among them you can see a range of mountains, " +
        "wide, flat moors, and south of those, the soaring " +
        "heights of Mount Kyrus.\n\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
    add_prop(OBJ_S_WIZINFO, "Player's _really_ shouldn't be " +
        "in here, and if you've found one here, trans 'em " +
        "out. This is just another temporary room for " +
        "Firestorm to fly through.\n");
}
