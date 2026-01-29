/*
 *	/d/Gondor/minas/shades/office.c
 *
 *	Modification log:
 *	20-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Shade;

public void
create_gondor()
{
    set_short("in the office of the Shades");
    set_long(BSN("This is the office of Arindel the Shade in the Shades' quarters. "
	+ "The room is well lit up by torches and lamps, and the flickering "
	+ "lights make strange shades and forms on the carved panel walls. A desk "
        + "stands in the centre of the room, and a throne-like seat stands behind "
        + "it. To the south is the door to the entrance hall of the quarters."));
    add_exit(MINAS_DIR + "shades/shadeentr", "south", 0, 0);
    clone_object(MINAS_DIR + "shades/priv_door")->move(TO);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

    reset_room();
}

public void
reset_room()
{
    Shade = clone_npc(Shade, COMMON_DIR + "quest/smuggler/arindel");
}
