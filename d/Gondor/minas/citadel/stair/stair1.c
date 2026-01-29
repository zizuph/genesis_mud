/*
 *  /d/Gondor/minas/citadel/stair/stair1.c
 *
 *  Stairwell of the White Tower: One
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

object door;

public void
create_gondor()
{
    set_short("Stairwell in the White Tower");
    set_long("This stairwell has hundreds of steps and rises fifty "
        + "fathoms in a spiral around the inside of the tower wall.\n");

    add_exit(INNER_MINAS + "/citadel/stair/stair2", "up", 0, 5);

    door = clone_object(INNER_MINAS + "/obj/throne_door_stair.c");
    door->move(TO);

    add_item(({"stairwell", "stairs", "steps", "tower", "spiral"}), 
        "Many broad steps "
        + "climb up from this place. They hug the inside wall of the "
        + "tower in a tight spiral.\n");
    add_item(({"wall", "walls", "tower wall", "stone", "native stone"}), 
        "The wall is made of smooth white native stone.\n");
    add_item(({"door"}), "You mean the stone door?\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    reset_room();
}



