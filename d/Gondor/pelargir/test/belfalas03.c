/*
 * /d/Gondor/pelargir/rooms/belfalas03.c
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
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        STREET_BELFALAS + " traverses a large stone bridge here,"
      + " crossing over the waters of the Sirith River which flow"
      + " beneath and then travel alongside " + STREET_BEACON
      + " on their way to join with the mighty Anduin, far to the"
      + " east.");

    add_item( ({ "bridge", "large bridge", "stone bridge",
                 "large stone bridge" }), BSN(
        "This bridge looks to be one of the oldest structures in"
      + " the city, judging by the great amount of vegetation and"
      + " lichen that cling to its stone sides. It is a very wide"
      + " structure, set with heavy masonry obviously intended"
      + " to allow large carriages and horse-drawn cargo to"
      + " cross two-abreast."));
    add_item( ({ "vegetation", "leafy vegetation" }), BSN(
        "Leafy vegetation clings in a thick swath to the underbelly"
      + " of the bridge, in some places nearly hanging down to the"
      + " surface of the water."));
    add_item( ({ "lichen", "stain", "stains", "dark stains" }), BSN(
        "Lichen has covered nearly every stone surface visible upon"
      + " the sides of the bridge, enjoying the constant sources of"
      + " both sunlight and moisture afforded by their position. The"
      + " new growth is mostly white and light green, while dark"
      + " stains are visible where the dead lichen yet clings."));
    add_item( ({ "waters", "water", "river", "river sirith",
                 "sirith", "sirith river" }), BSN(
        "The Sirith River flows beneath the bridge, travelling east"
      + " on its way to join with the mighty Anduin beyond the"
      + " city. Its waters are kept steady in their course by a"
      + " deep stone channel."));
    add_item( ({ "channel", "deep channel", "stone channel",
                 "deep stone channel" }), BSN(
        "The channel has tall sides which prevent the river from"
      + " deviating from its course even in the flood seasons."));
    add_item( ({ "anduin", "river anduin", "anduin river",
                 "mighty anduin" }), BSN(
        "The River Anduin is far to the east, and cannot be espied"
      + " from this location."));

    add_exit((PELAR_DIR + "test/belfalas02"), "northeast", 0);
    add_exit((PELAR_DIR + "test/belfalas04"), "southwest", 0);
} /* create_pelargir_room */
