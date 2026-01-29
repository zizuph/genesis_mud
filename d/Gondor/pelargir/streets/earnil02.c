/*
 * /d/Gondor/pelargir/rooms/earnil02.c
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
        "The road passes by an orphanage which is to the north, where"
      + " a number of children are visible playing amongst one another."
      + " To the east and west, more houses are visible, closely built"
      + " and unlovely to look at.");

    add_item( ({ "orphanage", "north" }), BSN(
        "Orphanages are rarely happy places to be, yet there is a"
      + " look of humble attempts to create what happiness can be"
      + " had about this one. Many children peek out from the doorway,"
      + " looking at others who play outside."));
    add_item( ({ "door", "doorway" }), BSN(
        "Children are peeking out of the doorway to the orphanage."));
    add_item( ({ "children", "child" }), BSN(
        "There are a lot of children around this area, many of whom"
      + " are busy playing with one another in the street."));

    add_exit((PELAR_DIR + "homes/orphanage"),  "north", 0);
    add_exit((PELAR_DIR + "streets/earnil03"),    "east", 0);
    add_exit((PELAR_DIR + "homes/shack1"),     "south", 0);
    add_exit((PELAR_DIR + "streets/earnil01"),     "west", 0);

} /* create_pelargir_room */
