/*
 * /d/Gondor/pelargir/rooms/peddlers03.c
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

    set_extra_desc(
        STREET_PEDDLERS + " meets with the docks to the north, where"
      + " the lane turns dramatically in that direction. A row of"
      + " shacks line the road to the north, each girded with"
      + " trophies along their porches which suggest that fishermen"
      + " might be the proud residents.");

    add_item( ({ "lane", "road", "street" }), BSN(
        "The lane takes a dramatic turn to the north here, where it"
      + " travels on to meet with the docks of Pelargir."));
    add_item( ({ "trophy", "trophies", "porch", "porches" }), BSN(
        "Various fish have been mounted on plaques and nailed to the"
      + " tops of the porches of some shacks along the north side"
      + " of the street here."));
    add_item( ({ "fish", "fishes", "plaque", "plaques" }), BSN(
        "Most of the fishes on the plaques are nothing to remark"
      + " over, but a few are truly large catches, making them a"
      + " worthy mount for the trophy. It would seem that bragging"
      + " rights mean something to the owners of these homes."));
    add_item( ({ "row", "row of shacks", "shack", "shacks" }), BSN(
        "A row of very similar looking shacks to the north side of"
      + " the road are distinguished by numerous trophies which"
      + " have been mounted on the porch of each."));

    add_exit((PELAR_DIR + "streets/peddlers02"), "west", 0);
    add_exit((PELAR_DIR + "homes/shack3"), "northwest", 0);
    add_exit((PELAR_DIR + "docks/dock8"), "north", 0);

} /* create_pelargir_room */
