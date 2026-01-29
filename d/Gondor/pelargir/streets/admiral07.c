/*
 * /d/Gondor/pelargir/rooms/admiral07.c
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
    set_part(PART_WEST);
    set_street_name(STREET_ADMIRAL);
    set_room_type(TYPE_STREET);

    set_extra_desc("The street comes to a dead end a little east of " +
        "here. Small buildings line the street to both sides.");

    add_item( ({ "east", "end", "dead end" }), BSN(
        "Down the street to the east, a dead end is visible,"
      + " shaded somewhat by the buildings in that direction."));
    add_item( ({ "building", "buildings", "small building",
                 "small buildings", "house", "houses", "small house",
                 "small houses" }), BSN(
            "Most of the houses " +
        "are in poor repair and seem to be derelict. To the north, " +
        "it is possible to enter a house through an open door, to " +
        "the south is an abandoned workshop."));
    add_item( ({ "door", "house" }), 
        BSN("The open door of this "+
          "house seems to have been badly battered."));
    add_item( ({ "workshop", }),
        BSN("The building south of the " +
        "street probably was the workshop of a craftsman before " +
        "it was abandoned. You can still see the place over the " +
        "door where a sign was inviting customers, but the sign " +
        "is missing."));
    add_item( ({ "sign", }), "It is missing.\n");


    add_exit((PELAR_DIR + "streets/admiral08"), "east", 0);
    add_exit((PELAR_DIR + "streets/belfalas06"), "west", 0);
    add_exit((PELAR_DIR + "homes/ranhome"),  "north", 0);
    add_exit((PELAR_DIR + "homes/abanshop"), "south", 0);

} /* create_pelargir_room */
