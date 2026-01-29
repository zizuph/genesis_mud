/*
 * /d/Gondor/pelargir/rooms/market02.c
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
    set_street_name(STREET_MARKET);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "Activity is a constant part of the scenery on " + STREET_MARKET
      + " which connects the docks to the east with Belfalas Square"
      + " to the west. South of here, the houses take on a very"
      + " practical look. This is clearly the working district of town.");

    add_item( ({ "crowd", "crowds", "crowd of people",
                 "crowds of people" }), BSN(
        "The crowds of people thicken to the west."));
    add_item( ({ "activity", "scenery" }), BSN(
        "People are constantly passing by on their way to one"
      + " destination or another. Many come from the east, laden"
      + " with commodities from the docks."));
    add_item( ({ "people", "person" }), BSN(
        "The people on the road here all look rather focused on"
      + " getting somewhere with whatever they have with them."));
    add_item( ({ "square", "belfalas square", "hub",
                 "main hub", "main hub of activity" }), BSN(
        "A ways to the west, the crowds thicken where Belfalas"
      + " Square opens up. It is definitely the main hub of activity"
      + " and business in Pelargir."));
    add_item( ({ "south", "district", "working district" }), BSN(
        "The people who own the dwellings to the south are clearly"
      + " not of the wealthy class, but rather must work hard for"
      + " the food on their tables. Signs of extra spending are"
      + " almost entirely absent."));

    add_exit((PELAR_DIR + "streets/market03"), "east", 0);
    add_exit((PELAR_DIR + "streets/market01"), "west", 0);

} /* create_pelargir_room */
