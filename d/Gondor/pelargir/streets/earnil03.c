/*
 * /d/Gondor/pelargir/rooms/earnil03.c
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
    set_street_name(STREET_EARNIL);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "A side street runs south towards the walls of the city,"
      + " to a decidedly unsavory part of Pelargir. East, the road"
      + " dwindles as it meets with the docks along the river. To"
      + " the west, a few children are visible playing in the street.");

    add_item( ({ "side street", "south" }), BSN(
        "A small side street runs away from " + STREET_EARNIL
      + " here, meeting with " + STREET_PEDDLERS + " along the"
      + " southern walls of the city to the south."));
    add_item( ({ "city walls", "wall", "walls", "walls of the city",
                 "southern city wall", "southern city walls" }), BSN(
        "The southern walls of the city are visible to the south,"
      + " looming over a side street which connects " + STREET_EARNIL
      + " with " + STREET_PEDDLERS + " in that direction."));
    add_item( ({ "unsavory part of pelargir", "unsavory part" }), BSN(
        "The area to the south, known as " + STREET_PEDDLERS + " is"
      + " not one of the more popular places in Pelargir."));
    add_item( ({ "child", "children", "west" }), BSN(
        "Children play in the street to the west. They also seem"
      + " to be coming and going from a house in that direction."));

    add_exit((PELAR_DIR + "docks/dock7"), "east", 0);
    add_exit((PELAR_DIR + "streets/earnil02"), "west", 0);
    add_exit((PELAR_DIR+  "streets/peddlers01"), "south", 0);

} /* create_pelargir_room */
