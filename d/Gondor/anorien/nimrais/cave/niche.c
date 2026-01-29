/*
 *	/d/Gondor/anorien/nimrais/cave/niche.c
 *
 *	December 1995, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
    set_short("a narrow niche");
    set_long(BSN("This is a narrow and shallow niche in the wall of the "
      + "tunnel. The tunnel is the the northwest. On all other sides are "
      + "cold and damp rock walls."));

    add_item(({"ground", "floor", "wall", "walls", "roof", "ceiling", }),
        BSN("The The niche is completely surrounded by cold and damp "
      + "rock walls, save for the exit to the northwest."));

    add_exit(ANO_DIR + "nimrais/cave/tunnel1", "northwest", 0, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}

