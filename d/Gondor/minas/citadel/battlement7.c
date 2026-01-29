/*
 *  /d/Gondor/minas/citadel/battlement7.c
 *
 *  Stairs to the Battlement: Stairs Six
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_gondor()
{
    set_short("On the stairs below the Battlement");
    set_long("This is a wide flight of stairs leading up to the Battlement. "
        + "After the closeness of the circles of the city, this place "
        + "feels wide open and breezy. Not much can be seen from here, "
        + "however, because the great bastion of stone blocks the "
        + "view to the east, whereas Mount Mindolluin dominates the "
        + "western horizon.\n");

    add_exit(INNER_MINAS + "/citadel/battlement8", "up", 0, 1);
    add_exit(INNER_MINAS + "/citadel/battlement6", "down", 0, 1);

    add_battlement_items();

    add_prop(ROOM_I_INSIDE, 0);

    set_tell_time(120);

    add_battlement_tells();

    reset_room();

}   


/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}




