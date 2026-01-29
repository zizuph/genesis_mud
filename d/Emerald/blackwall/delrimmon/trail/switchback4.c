/*
 *  /d/Emerald/blackwall/delrimmon/trail/switchback4.c
 *
 *  This is the uppermost point of the switchbacks which lead into
 *  the Del Rimmon area.
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
public int         climb_boulders(string arg);
public void        init();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("on some switchbacks in the Blackwall Mountains");

    set_long("The switchbacks are just below what appears to be a ridge"
      + " of some kind to the east, where the trail disappears over"
      + " a bluff in that direction. To the southeast, the trail"
      + " descends into the mist, and is lost from sight. A few"
      + " boulders lie clustered close to the cliff wall here.\n");
 
    add_item( ({ "ridge", "bluff", "east" }),
        "To the east, the trail disappears over a ridge. It appears as"
      + " if the switchbacks end in that direction.\n");
    add_item( ({ "boulder", "boulders", "cluster" }),
        "Just before the cliff wall to the north, a few large boulders"
      + " are piled in a cluster of sorts. They are each almost as"
      + " tall as an average male human.\n");
    add_item( ({ "cliff wall", "wall", "wall of the cliff", "north" }),
        "The cliff wall to the north is hard and sheer, rising many"
      + " hundreds of feet above. A few large boulders lie clustered"
      + " here near the trail.\n");


    add_switchback_items();


    add_exit(DELRIMMON_DIR + "lakeside/pathway1", "east",
             0, 10, 0);
    add_exit(DELRIMMON_DIR + "trail/switchback3", "southeast",
             0, 5, 0);

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


/*
 * Function name:        climb_boulders
 * Description  :        let players try to climb the boulders
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_boulders(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to climb?\n");
    }

    if (!parse_command(arg, ({}),
        "[up] [over] [on] [onto] [to] [the] [large] "
      + "'boulder' / 'boulders' / 'cluster'"))
    {
        return 0; /* bad syntax */
    }

    write("You clamber up onto one of the boulders. There really doesn't"
      + " seem to be any advantage to being up here, and so you jump"
      + " down onto the path once more.\n");
    return 1;
} /* climb_boulders */


/*
 * Function name:        init
 * Description  :        add some actions to the players
 */
public void
init()
{
    ::init();

    add_action(climb_boulders, "climb");
} /* init */
