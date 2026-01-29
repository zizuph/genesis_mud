/*
 *  /d/Gondor/minas/citadel/stair/stair22.c
 *
 *  Stairwell of the White Tower: Twenty-two
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("Near the top of the White Tower");
    set_long("This stairwell has hundreds of steps and rises fifty "
        + "fathoms in a spiral around the inside of the tower wall. "
        + "Just above you the stairwell comes to an end.\n");
    add_item(({"stairwell", "stairs", "steps", "tower", "spiral"}), 
        "Many broad steps "
        + "climb up from this place. They hug the inside wall of the "
        + "tower in a tight spiral.\n");
    add_item(({"wall", "walls", "tower wall", "stone", "native stone"}), 
        "The wall is made of smooth white native stone.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);
    

    add_exit(INNER_MINAS + "/citadel/palantir_room", "up", 0, 5);
    add_exit(INNER_MINAS + "/citadel/stair/stair21", "down", 0, 1);

    reset_room();
}



