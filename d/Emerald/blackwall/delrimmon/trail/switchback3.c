/*
 *  /d/Emerald/blackwall/delrimmon/trail/switchback3.c
 *
 *  This is part of the switchbacks which lead up into the Del Rimmon
 *  area. Here, mist from the waterfall has shrouded the room in a
 *  cloud of sorts.
 *
 *  Copyright (c) December 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/trail/switchback1";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */

/* prototypes */
public void        create_del_rimmon();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("on some switchbacks in the Blackwall Mountains");

    set_long("Visibility is extremely poor here, where the switchbacks"
      + " which form this zig-zagging trail have come as close as they"
      + " dare to Rimmon Falls. Just to the east, a thunderous and"
      + " pounding chorus of water falls endlessly from high above,"
      + " sending dense clouds of water vapour into the vicinity. You"
      + " are able to dimly make out the trail sloping upward round"
      + " a tight bend to the northwest, or one could head down the"
      + " path to the west.\n");

    add_item( ({ "waterfall", "falls", "rimmon falls", "water",
                 "east" }),
        "Just to the east, the mighty Rimmon Falls roar downwards"
      + " to feed the waters of the River Telberin. A great deal of"
      + " mist and vapour have drifted into the area, making"
      + " visibility extremely poor.\n");
    add_item( ({ "mist", "vapor", "vapour", "water vapor",
                 "waver vapour", "visibility", "cloud", "clouds" }),
        "Mist and water vapour from Rimmon Falls to the east have"
      + " created a veritable cloud here, making visibility extremely"
      + " poor. The mist clings to everything, including your"
      + " clothing.\n");


    add_switchback_items();

    add_exit(DELRIMMON_DIR + "trail/switchback2", "west",
             0, 5, 0);
    add_exit(DELRIMMON_DIR + "trail/switchback4", "northwest",
             0, 10, 0);
    set_no_exit_msg( ({ "north", "northeast" }),
        "The cliffs block your movement in that direction.\n");
    set_no_exit_msg( ({ "east", "southeast", "south",
                        "southwest" }),
        "The fall from the dropoff in that direction would"
      + " surely be your last.\n");
    set_no_exit_msg( ({ "down" }),
        "You can travel down the switchbacks to the west.\n");
    set_no_exit_msg( ({ "up" }),
        "You can travel up the switchbacks to the northwest.\n");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
} /* create_del_rimmon */
