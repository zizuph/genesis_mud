/*
 * /d/Gondor/pelargir/rooms/earnil01.c
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

    set_extra_desc(
        "To the west lies a pile of trash and debris so big it blocks " +
        "the road. To the east the road continues on past an " +
        "orphanage to the docks, and to the north a small side street " +
        "leads to the main road.");
    add_item( ({ "trash", "debris", "trash and debris" }),
        BSN("The pileup blocks the road so perfectly it seems that " +
        "it must be intentional. If it didn't stink so bad " +
        "and attract so many disguisting vermin, you might " +
        "be curious as to what is on the other side."));
    add_item("orphanage",
        "The orphanage does not look like a happy place to be.\n");

    add_exit((PELAR_DIR + "test/market03"), "north", 0);
    add_exit((PELAR_DIR + "test/earnil02"), "east", 0);

} /* create_pelargir_room */
