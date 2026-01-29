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
        "This street enters the residential district for the working"
      + " class citizens of Pelargir. Many homes are all around, most"
      + " of which are charactarized by a strict functionality, which"
      + " speaks less of wealth than the need to work to survive."
      + " The road continues to the east, where a few children"
      + " can be seen playing.");

    add_item( ({ "district", "residential district" }), BSN(
        "This area is defined by homes which have been build simply"
      + " to cover the heads of the owners. There is nothing which"
      + " speaks of money or spare time."));
    add_item( ({ "east", "children", "child" }), BSN(
        "There are a few children playing in the street to the"
      + " east."));

    add_exit((PELAR_DIR + "streets/market03"), "north", 0);
    add_exit((PELAR_DIR + "streets/earnil02"), "east", 0);

} /* create_pelargir_room */
