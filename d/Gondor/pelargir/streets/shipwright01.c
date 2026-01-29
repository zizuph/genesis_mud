/*
 * /d/Gondor/pelargir/rooms/shipwright01.c
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
    set_street_name(STREET_SHIPWRIGHT);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "The docks of Pelargir run parallel to " + STREET_SHIPWRIGHT
      + " to the east, which ends to the south, where it meets with "
      + STREET_MARKET + ". A warehouse stands on the corner here.");

    add_item( ({ "warehouse", "large warehouse" }), BSN(
        "Similar to the many warehouses that are visible along this"
      + " street, it is large, and looks capable of storing large"
      + " quantities of goods offloaded by the ships at port."));
    add_item( ({ "corner" }), BSN(
        "A warehouse stands on the corner here, where "
      + STREET_SHIPWRIGHT + " joins with " + STREET_MARKET + "."));

    add_exit((PELAR_DIR + "streets/shipwright02"), "north", 0);
    add_exit((PELAR_DIR + "docks/dock5"), "east", 0);
    add_exit((PELAR_DIR + "streets/market04"), "south", 0);
    add_exit((PELAR_DIR + "docks/warehouse4"),  "west",  0);

} /* create_pelargir_room */
