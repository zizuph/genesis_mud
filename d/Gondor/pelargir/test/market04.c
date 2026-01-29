/*
 * /d/Gondor/pelargir/rooms/market04.c
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
    set_part(PART_EAST);
    set_street_name(STREET_MARKET);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "The docks of Pelargir are just to the east here, their"
      + " creaking timbers audible even from a distance. Ships are"
      + " visible lining the many docks, in many cases with a proud"
      + " captain and his crew fussing over some aspect of a"
      + " shipment or repair need. " + STREET_SHIPWRIGHT + " runs to"
      + " the north, bordering a series of low buildings.");

    add_item( ({ "timber", "timbers", "creaking",
                 "creaking timber", "creaking timbers" }), BSN(
        "The sound of creaking timbers accompanies the view of the"
      + " docks to the east."));
    add_item( ({ "captain", "proud captain", "crew", "crews", "people",
                 "captains", "proud captain and his crew" }), BSN(
        "Many people are visible on the docks. Some of them look"
      + " more important than others."));
    add_item( ({ "low buildings" }), BSN(
        "The buildings which run alongside " + STREET_SHIPWRIGHT
      + " to the north look somewhat dingy. A few warehouses are"
      + " visible, as well as what looks to be a pub."));
    add_item( ({ "pub", "bar" }), BSN(
        "The pub is a ways to the north, so the view from here is"
      + " of little use."));
    add_item( ({ "warehouse", "warehouses" }), BSN(
        "Warehouses are all around the port of Pelargir. A few are"
      + " visible along the road to the north."));

    add_exit((PELAR_DIR + "test/shipwright01"), "north", 0);
    add_exit((PELAR_DIR + "docks/dock6"), "east", 0);
    add_exit((PELAR_DIR + "test/market03"), "west", 0);

} /* create_pelargir_room */
