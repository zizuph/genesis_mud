/*
 * /d/Gondor/pelargir/rooms/peddlers03.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"


public void	create_pelargir_room();


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_SOUTH);
    set_street_name(STREET_PEDDLERS);
    set_room_type(TYPE_STREET);

    set_extra_desc("The lane takes a dramatic turn among the fisherman's " +
        "shacks here. To the west the lane leads farther into the poor " +
        "southern section of Pelargir, and to the north you can see " +
        "one of the docks.");

    add_exit((PELAR_DIR + "test/peddlers02"), "west", 0);
    add_exit((PELAR_DIR + "homes/shack3"), "northwest", 0);
    add_exit((PELAR_DIR + "docks/dock8"), "north", 0);

} /* create_pelargir_room */
