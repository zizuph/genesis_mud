/*
 * /d/Gondor/pelargir/rooms/beacon01.c
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

static object  Citizen;

public void	create_pelargir_room();
public void	reset_room();



/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "Various buildings line the north side of the road here,"
      + " where " + STREET_BEACON + " runs east towards a distant"
      + " stone structure on the horizon. Just to the south, the"
      + " Sirith River flows alongside of the road in a reinforced"
      + " channel.");

    add_item( ({ "beacon", "lighthouse", "stone structure",
        "structure", "outline", "horizon" }),
        BSN("A ways off to the east, the outline of a large stone " +
            "structure rises into view. It appears to be a " +
            "lighthouse."));
    add_item( ({ "river", "river sirith", "sirith", "sirith river",
        "water", "waters", "south", }),
        BSN("To the south, the River Sirith runs parallel to Beacon " +
            "Street, guided in its path by a reinforced channel which " +
            "has been framed with stone."));
    add_item( ({ "channel", "reinforced channel", }),
        BSN("The waters of the river flow quietly along in the " +
            "channel which has kept the river on its course for " +
            "many years."));

    add_exit((PELAR_DIR + "test/belfalas02"), "west", 0);
    add_exit((PELAR_DIR + "test/beacon02"), "east", 0);

    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create citizen
 */
public void
reset_room()
{
    Citizen = clone_npc(Citizen, CITIZEN_FILE);
} /* reset_room */
