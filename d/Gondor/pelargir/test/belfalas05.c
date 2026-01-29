/*
 * /d/Gondor/pelargir/rooms/belfalas05.c
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
    set_part(PART_WEST);
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "A majestic building layered with marble frames the west"
      + " side of the street here, spanning a wide area as its"
      + " chambers extend outward in many wings from the main"
      + " building. " + STREET_BELFALAS + " runs on to the north"
      + " and south.");

    add_item( ({ "building", "majestic building", "main building",
                 "main hall", "hall", "house of the dunedain",
                 "houses of the dunedain" }), BSN(
        "The building is roofed by a large dome and seems to be"
      + " built around a large central hall that must be able to"
      + " hold a considerable portion of the population of the city."));
    add_item( ({ "cupola", "majestic cupola", "dome",
                 "large dome" }), BSN(
        "A sense of marvel accompanies the majestic cupola on the"
      + " building to the west. From where you stand it appears"
      + " almost to float above the building, so light and"
      + " uplifting does it look, but a closer look reveals that it"
      + " was constructed out of massive black rock and must be"
      + " incredily heavy. Only the craft of the men of Westernesse"
      + " at its zenith could create such miracles."));
    add_item( ({ "central hall" }), BSN(
        "The central hall of the building is monstrous in proportions,"
      + " giving it the look of something meant to hold vast quantities"
      + " of people at any one time. It is layered with huge slabs"
      + " of marble."));
    add_item( ({ "marble", "slab", "slabs", "huge slab", "huge slabs",
                 "slab of marble", "slabs of marble",
                 "huge slab of marble",
                 "huge slabs of marble" }), BSN(
        "The central hall of the building is covered from end to end"
      + " with huge slabs of marble, which have been hewn with great"
      + " care and expertise."));

    add_exit((DUNEDAIN_DIR + "rooms/hall"), "west", 0);
    add_exit((PELAR_DIR + "test/belfalas04"), "north", 0);
    add_exit((PELAR_DIR + "test/belfalas06"), "south", 0);

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
