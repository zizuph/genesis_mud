/*
 * /d/Gondor/pelargir/rooms/peddlers01.c
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

    set_extra_desc("This section of Pelargir is " +
        "populated entirely by shacks and shanties. The people here " +
        "are obviously too poor to afford much, though they do not seem " +
        "to mind a whole lot. The street continues to the east, though " +
        "unfortunately the western section is barricaded off by " +
        "construction. A small side street goes north.");

    add_item("construction",
        BSN("It consists of many stone bricks, " +
        "quite a few timbers, and no small amount of grime."));
    add_item( ({ "shack", "shacks", "shanty", "shanties",
                 "shacks and shanties" }), BSN(
        "The homes here along " + STREET_PEDDLERS + " are very"
      + " humble indeed. In many cases, there is hardly a servicable"
      + " roof overhead to keep out the rainwater."));

    add_exit((PELAR_DIR + "streets/earnil03"),  "north",      0);
    add_exit((PELAR_DIR + "homes/shack2"),   "northeast",  0);
    add_exit((PELAR_DIR + "streets/peddlers02"),  "east",       0);

} /* create_pelargir_room */
