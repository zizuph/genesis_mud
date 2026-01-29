/*
 * /d/Gondor/pelargir/rooms/belfalas02.c
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
        "A three-way intersection here marks the meeting place of "
      + STREET_BELFALAS + " with " + STREET_BEACON + ". Just to the"
      + " southwest, the Sirith River is visible flowing silently"
      + " beneath a bridge which spans the stone channel that"
      + " keeps the waters in their course. Far off to the east,"
      + " a tall stone structure is visible against the sky.");

    add_item( ({ "channel", "stone channel" }), BSN(
        "A stone channel has been constructed to keep the Sirith"
      + " River in its course as it travels east through the"
      + " city."));
    add_item( ({ "intersection", "three way intersection",
                 "three-way intersection" }), BSN(
        "The intersection connects the north-south running "
      + STREET_BELFALAS + " with " + STREET_BEACON + " which"
      + " travels to the east."));
    add_item( ({ "bridge", "aged bridge" }),
        BSN("The aged bridge spans the Sirith River, and heads " +
            "deeper into the city."));
    add_item( ({ "lighthouse", "structure", "stone structure",
        "tall stone structure" }), 
        BSN("From this distance, all that is visible is a tall " +
            "stone structure."));
    add_item( ({ STREET_BEACON, "east" }), BSN(
        STREET_BEACON + " runs far to the east, where it seems to"
      + " end before a distant stone structure."));
    add_item( ({ "sirith", "water", "waters", "river",
                 "sirith river", "river sirith" }), BSN(
        "The Sirith River flows east, travelling underneath a bridge"
      + " to the southwest to flow parallel to " + STREET_BEACON
      + " as it travels into the distance."));

    add_exit((PELAR_DIR + "streets/belfalas01"), "north", 0);
    add_exit((PELAR_DIR + "streets/beacon01"),    "east",      0);
    add_exit((PELAR_DIR + "streets/belfalas03"), "southwest", 0);

} /* create_pelargir_room */
