/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff2.c
 *
 *  The cliffs which extend along the borders of the northwestern
 *  rim of the basin of Del Rimmon in the Blackwall Mountains of Emerald
 *  extend quietly to the northeast and southwest here.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with area presets
 */
public void
create_cliff_room()
{
    set_loc(3);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("The line of tall cliffs winds gradually in a"
                + " wide arc, trailing away in the distance both"
                + " to the northeast and southwest.");

    add_item( ({"line", "line of cliffs", "line of tall cliffs",
                "tall cliffs"}), BSN(
        "The cliffs extend for a good distance as one follows them"
      + " to the northeast and southwest, gradually tracing the"
      + " contours of the lake."));
    add_item( ({"contours of the lake", "contours"}), BSN(
        "The contours of the lake are nearly traced from a distance"
      + " by the cliffs in this area."));
    add_item( ({"arc", "wide arc"}), BSN(
        "The cliffs curve gently as they extend away in both"
      + " directions."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff3","northeast");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1","southwest");

    set_no_exit_msg( ({ "west", "northwest", "north" }),
        "The cliff walls prevent you from moving in that direction.\n");
} /* create_cliff_room */

/*
 * Function name: init
 * Description  : Add actions to the player.
 */
public void
init()
{
    ::init();

    add_action(em_climbing_hook, "climb");
} /* init */
