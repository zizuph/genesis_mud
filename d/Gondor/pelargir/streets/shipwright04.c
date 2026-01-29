/*
 * /d/Gondor/pelargir/rooms/shipwright04.c
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


static object  Sailor;

public void	create_pelargir_room();
public void	reset_room();


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_EAST);
    set_street_name(STREET_SHIPWRIGHT);
    set_room_type(TYPE_STREET);

    set_extra_desc("The street continues " +
        "to its end north of here, and runs past several buildings to " +
        "the south. Peals of bawdy laughter and sailor songs ring " +
        "from a building to the west, and the many docks of Pelargir " +
        "extend along the shore to the east.");

    add_item( ({ "end", "north", "end of the street" }), BSN(
        STREET_SHIPWRIGHT + " seems to come to an end just a bit to"
      + " the north."));
    add_item( ({ "laughter", "bawdy laughter", "songs",
                 "sailor songs", "west", "building", "pub",
                 "building to the west" }), BSN(
        "The building to the west bears all the familiar signs of"
      + " being the local pub."));

   add_exit((PELAR_DIR + "streets/shipwright05"), "north", 0);
   add_exit((PELAR_DIR + "misc/sailor_pub"), "west", 0);
   add_exit((PELAR_DIR + "streets/shipwright03"), "south", 0);
   add_exit((PELAR_DIR + "docks/dock2"), "east", 0);


    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create citizen
 */
public void
reset_room()
{
    Sailor = clone_npc(Sailor, SAILOR_FILE);
} /* reset_room */
