/*
 * /d/Gondor/pelargir/rooms/peddlers02.c
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

    set_extra_desc("The shacks along this street all need desperate remodelling " +
        "attention as a few of them seem to be held together by no " +
        "more than twine.");

    add_exit((PELAR_DIR + "test/peddlers01"), "west", 0);
    add_exit((PELAR_DIR + "test/peddlers03"), "east", 0);

} /* create_pelargir_room */
