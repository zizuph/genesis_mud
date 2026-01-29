/*
 * /d/Gondor/pelargir/rooms/earnil03.c
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
    set_street_name(STREET_EARNIL);
    set_room_type(TYPE_STREET);

    set_extra_desc("This area of Pelargir seems to be run down, and ill " +
        "used. There is a slight stench here that may be coming " +
        "from the docks east of here. " +
        "Another side road leads to the south, while this road runs " +
        "west to an orphanage and east to the docks ");

    add_item("orphanage",
        "The orphanage does not look like a happy place.\n");

    add_exit((PELAR_DIR + "docks/dock7"), "east", 0);
    add_exit((PELAR_DIR + "test/earnil02"), "west", 0);
    add_exit((PELAR_DIR+  "test/peddlers01"), "south", 0);

} /* create_pelargir_room */
