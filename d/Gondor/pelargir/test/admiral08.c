/*
 * /d/Gondor/pelargir/rooms/admiral08.c
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

static object	Ruffian1, Ruffian2;

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
    set_street_name(STREET_ADMIRAL);
    set_room_type(TYPE_STREET);

    set_extra_desc("The road here comes upon " +
        "the back of some building and is hedged in by houses to the " +
        "north and south. Because of the height of the building it is " +
        "exceptionally shady and dark here.");

    add_item( ({ "back", "back of the building", "building back",
                 "back of a tall building", "tall building",
                 "building" }), BSN(
        "The building is rather tall, with a roof that overhangs"
      + " the street high above, casting the area in a cover of"
      + " darkness. There are no features on this side of the"
      + " building aside from a few dark stains on the wall."));
    add_item( ({ "roof", "roof of the building" }), BSN(
        "The roof of the building overhangs the street somewhat,"
      + " casting the area in shadow."));
    add_item( ({ "side", "side of the building", "stain", "stains",
                 "dark stain", "dark stains", "few dark stains" }), BSN(
        "The stains appear to have been made by someone thowing a"
      + " bottle of liquid at the building."));
    add_item( ({ "shadow", "shade", "darkness", "cover",
                 "cover of darkness" }), BSN(
        "This area is somewhat dark, and does not have a particularly"
      + " wholesome feel to it."));

    add_exit((PELAR_DIR + "test/admiral07"), "west", 0);

    reset_room();
} /* create_pelargir_room */


/*
 * Function name:	reset_room
 * Description	:	create ruffians
 */
public void
reset_room()
{
    Ruffian1 = clone_npc(Ruffian1, RUFFIAN_FILE);
    Ruffian2 = clone_npc(Ruffian2, RUFFIAN_FILE);
} /* reset_room */
