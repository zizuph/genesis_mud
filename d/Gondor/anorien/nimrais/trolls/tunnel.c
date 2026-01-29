/*
 * /d/Gondor/anorien/nimrais/trolls/tunnel.c
 *
 * Coder: Unknown
 *
 * Modification log:
 * Gwyneth, 10/02/02: Updated and cleaned up the code. Changed inheritance.
 */
inherit "/d/Gondor/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("a narrow tunnel in the lair of the hill-trolls");
    set_long("The cave to the north becomes narrower and turns into a " +
        "tunnel leading downwards. A thin stream of water is trickling " +
        "down on the ground.\n");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NIMRAIS_DIR + "trolls/prisoncave", "north", 0, 0);
    add_exit(NIMRAIS_DIR + "cave/tunnel3",      "down",  0, 2);

    add_item(({"ground", "floor", }),
        "The ground is covered with small stones and pebbles and rather wet " +
        "from the water trickling down in this tunnel.\n");
    add_item( ({"water", "stream", }),
        "The thin stream of water comes trickling into the tunnel from the " +
        "cave to the north and disappears down into the tunnel.\n");
}

