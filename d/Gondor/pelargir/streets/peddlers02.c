/*
 * /d/Gondor/pelargir/rooms/peddlers02.c
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
        STREET_PEDDLERS + " runs directly alongside the southern"
      + " walls of the city here, which loom high overhead, their"
      + " dirty sides caked with moss and vegetation. The atmosphere"
      + " here is one of disrepair and poverty.");

    add_item( ({ "wall", "walls", "southern wall", "southern walls",
                 "southern walls of the city",
                 "southern wall of the city" }), BSN(
        "The wall shades this area from much of the sunlight during"
      + " the day, and at night provides shadows that are long and"
      + " deep. It is not the safest place in the city."));
    add_item( ({ "side", "sides", "dirty side", "dirty sides",
                 "side of the wall", "sides of the wall",
                 "side of the walls", "sides of the walls" }), BSN(
        "The walls are caked with moss and vegetation, which have"
      + " grown over many years and never been cleaned away."));
    add_item( ({ "moss", "vegetation" }), BSN(
        "The moss and vegetation along the walls give the area"
      + " a dirty and depressing atmosphere. No one has bothered"
      + " to clean them for what appears to be decades."));

    add_exit((PELAR_DIR + "streets/peddlers01"), "west", 0);
    add_exit((PELAR_DIR + "streets/peddlers03"), "east", 0);

} /* create_pelargir_room */
