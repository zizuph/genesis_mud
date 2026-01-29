/*
 * /d/Gondor/pelargir/rooms/beacon03.c
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
    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "North of the road, a green lawn runs towards the base of the"
      + " city walls, where a few soldiers are visible patrolling"
      + " along the battlement. The Sirith River flows quietly in"
      + " its channel to the south. A lighthouse is visible in the"
      + " distance to the east.");

    add_item( ({ "lawn", "green lawn" }), BSN(
        "There are no dwellings or other buildings placed on this"
      + " lawn. Perhaps it is privately owned."));
    add_item( ({ "wall", "walls", "city wall", "city walls",
                 "base", "base of the city walls",
                 "base of the walls" }), BSN(
        "The northern walls of the city have stood for many centuries,"
      + " and are constantly patrolled."));
    add_item( ({ "solider", "soldiers", "few soldiers" }), BSN(
        "The soldiers upon the battlements are a good distance to the"
      + " north. From this vantage point, you can only see their faint"
      + " outlines atop the city walls."));
    add_item( ({ "battlement", "battlements" }), BSN(
        "The battlements upon the city walls are constantly patrolled"
      + " by the soldiers of Pelargir. A few are visible even now."));
    add_item( ({ "river", "water", "river sirith", "sirith river",
                 "sirith", "waters" }), BSN(
        "Just south of the street, the Sirith River flows quietly by in"
      + " the narrow stone channel which guides it through the city."));
    add_item( ({ "channel", "stone channel", "narrow channel", 
                 "narrow stone channel" }), BSN(
        "The channel keeps the waters of the river in their course,"
      + " even in the flood seasons."));
    add_item( ({ "lighthouse", "structure", "stone structure",
                 "tall stone structure", "tall structure" }), BSN(
        "To the east, the tall stone structure of a lighthouse is"
      + " visible in the distance."));


    add_exit((PELAR_DIR + "test/beacon04"), "east", 0);
    add_exit((PELAR_DIR + "test/beacon02"), "west", 0);

} /* create_pelargir_room */
