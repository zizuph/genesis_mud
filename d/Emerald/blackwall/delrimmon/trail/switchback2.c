/*
 *  /d/Emerald/blackwall/delrimmon/trail/switchback2.c
 *
 *  This is the part of the switchback trail which leads up
 *  to Del Rimmon.
 *
 *  Copyright (c) November 2001, by Cooper Sherry (Gorboth)
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

    set_long("The switchbacks continue up the side of the cliff here,"
      + " where the trail makes yet another sharp turn as it angles"
      + " slowly upward. A few deep cracks are visible in the side"
      + " of the cliff here, just to the north of the path. To the"
      + " east, one can follow the trail upwards, or head down the"
      + " switchbacks by travelling southeast.\n");

    add_item( ({ "crack", "cracks", "deep crack", "deep cracks",
                 "side", "side of the cliff", "side of the cliffs",
                 "cliff side", "cliff sides", "cliffside", "cliffsides" }),
        "Deep cracks are visible in the cliffs to the north of the"
      + " path here. They do not have the worn and aged looks of the"
      + " other textures of the slope. Rather, they appear to have"
      + " been made in the not too distant past by some violence -"
      + " perhaps an earthquake or some such.\n");


    add_switchback_items();

    add_exit(DELRIMMON_DIR + "trail/switchback1", "southeast",
             0, 5, 0);
    add_exit(DELRIMMON_DIR + "trail/switchback3", "east",
             0, 10, 0);
    set_no_exit_msg( ({ "down" }),
        "You can travel down the switchbacks to the southeast.\n");
    set_no_exit_msg( ({ "up" }),
        "You can travel up the switchbacks to the east.\n");
    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "The cliffs rise to block you in that direction.\n");
    set_no_exit_msg( ({ "south", "southwest", "west" }),
        "You stop at the edge of a sheer drop in that direction.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
} /* create_del_rimmon */
