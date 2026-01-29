/*
 * /d/Gondor/pelargir/rooms/market03.c
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
        "From this point, the docks to the east are in nearly plain"
      + " sight. A whole way of life plays itself out here in Pelargir"
      + " every day based entirely on the coming and going of ships"
      + " to port. A lane runs to the south, where a residential"
      + " district lies.");

    add_item( ({ "lane", "shallow lane", "south" }), BSN(
        "A shallow lane makes its way between a few houses to the"
      + " south, to connect with " + STREET_EARNIL + " deeper"
      + " within the residential district."));
    add_item( ({ "district", "residential district" }), BSN(
        "Homes crowd the street to the south, where a residential"
      + " district for the working class of Pelargir spreads out."));

    add_exit((PELAR_DIR + "streets/market04"), "east", 0);
    add_exit((PELAR_DIR + "streets/earnil01"), "south", 0);
    add_exit((PELAR_DIR + "streets/market02"), "west", 0);

} /* create_pelargir_room */
