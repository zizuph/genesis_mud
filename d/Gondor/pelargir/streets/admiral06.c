/*
 * /d/Gondor/pelargir/rooms/admiral06.c
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
    set_street_name(STREET_ADMIRAL);
    set_room_type(TYPE_STREET);

    set_extra_desc("This is the garden district of Pelargir, mostly " +
       "populated by the wealthy. To the north lies one of the larger " +
       "houses, owned by one of the oldest families in Pelargir. " +
       "East will lead you to Belfalas Way.");

    add_item( ({ "garden district", "district" }), BSN(
        "This area of town has come to be called the garden district,"
      + " due to the many affluent members of the community who"
      + " live here, often in large mansions with many gardens."));
    add_item( ({ "garden", "gardens" }), BSN(
        "Many gardens are visible in this district of town, tended"
      + " carefully by the servants of wealthy landlords."));
    add_item( ({ "mansions", "houses", "home", "homes",
                 "dwelling", "dwellings", "building",
                 "buildings" }), BSN(
        "The houses in this area are nearly all large and exhibit"
      + " signs of wealth and affluence in society."));
    add_item( ({ "north", "larger houses", "larger house",
                 "large mansion", "large home" }), BSN(
        "To the north, one of the largest mansions is visible."));
    add_item( ({ "east", "belfalas way" }), BSN(
        "To the east, " + STREET_ADMIRAL + " passes through "
      + STREET_BELFALAS + " before continuing onward."));

    add_exit((PELAR_DIR + "homes/mangarden"), "north", 0);
    add_exit((PELAR_DIR + "streets/belfalas06"), "east", 0);

} /* create_pelargir_room */
