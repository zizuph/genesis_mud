/* Ashlar, 6 Jul 97 - The Neraka public board */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit INNER_IN;

void
create_neraka_room()
{
    set_short("the Neraka public forum");
	
    set_long("This small building houses a bulletin board used by the " +
        "public. An oil lamp hanging from the ceiling spreads light " +
        "in the room, and a few chairs are placed along the walls. " +
        "To the east, an exit leads out.\n");

    add_item_inside();
    add_item(({"lamp", "oil lamp"}),
        "The lamp is burning with a soft yellow light, illuminating the " +
        "room.\n");
    add_item(({"chair","chairs","wooden chair","wooden chairs"}),
        "The chairs are made of dark wood, and are of good make, but they " +
        "do not look very comfortable.\n");

    add_exit(NINNER + "r4","east");

    clone_object(NOBJ + "inner_board")->move(TO);
}

