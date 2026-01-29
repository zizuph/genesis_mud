/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/outpost_corridor.c
 *
 *  This corridor runs between the outpost barracks and the inner
 *  chamber leading to the signal.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a dark corridor");
    set_long(BSN(
        "A corridor turns from its southwestern exit here, running"
      + " to the north. The stone walls of this place appear very"
      + " narrow, advancing toward total darkness to the south, and a"
      + " dimly lit chamber to the north."));

    add_item( ({ "corridor", "here", "passage", "passageway",
                 "tunnel" }), BSN(
        "This corridor is extremely narrow, and bare of any decor."));
    add_item( ({ "southwest", "southwestern exit" }), BSN(
        "The exit to the southwest appears to lead into a dark"
      + " chamber."));
    add_item( ({ "north", "northern exit", "chamber",
                 "dimly lit chamber", "chamber to the north",
                 "northern chamber", "dimly lit chamber to the north" }),
        "North of here, the corridor proceeds into a dimly lit chamber."
      + " Nothing much can be seen without first travelling that"
      + " direction.\n");
    add_item( ({ "dark", "darkness", "total darkness" }), BSN(
        "The darkness is thick and heavy. You can only guess at"
      + " what lies beyond it."));
    add_item( ({ "wall", "walls", "stone wall", "stone walls" }), BSN(
        "The stone walls of this corridor appear to have been hewn"
      + " from the very rock of the cliffs."));
    add_item( ({ "rock", "rock of the cliffs", "stone" }), BSN(
        "The stone is very rough, and appears to have been somewhat"
      + " hastily carved."));
    add_item( ({ "floor", "ground", "down" }), BSN(
        "The floor is covered with a great deal of dust in this"
      + " corridor."));
    add_item( ({ "dust" }), BSN(
        "There are footprints in the dust here."));
    add_item( ({ "print", "footprint", "prints", "footprints" }), BSN(
        "The footprints are by no means fresh, and have themselves"
      + " been filled by a rather thick layer of dust. They appear"
      + " to be leading to the north."));
    add_item( ({ "sky", "sun", "moon" }), BSN(
        "The sky is not visible from within this stone corridor."));
    add_item( ({ "cliff", "cliffs", "cliffside", "cliffsides" }), BSN(
        "You are within the cliffs, and cannot view them as though"
      + " you were not."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1b", "north");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1", "southwest");

    set_no_exit_msg( ({ "northwest", "west", "south", "southeast",
                        "east", "northeast" }),
        "The corridor walls bar the way.\n");
} /* create_del_rimmon */
