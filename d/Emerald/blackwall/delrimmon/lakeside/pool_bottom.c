/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/pool_bottom.c
 *
 *  This is the underwater room which can be reached by diving into the
 *  pool at: /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff1.c
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "d/Emerald/blackwall/delrimmon/lakeside/caves/pool_bottom";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public int         do_swim(string arg);
public void        init();


/*
 * function name:        create_del_rimmon
 * descripiton  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_pool");
    set_short("beneath the waters of a deep pool");

    set_long("Slimy rocks form the basin for this very deep pool of"
           + " water beneath the falls. Dark water churns all around"
           + " you, stirring up small bits of refuse which cling to"
           + " the bottom and sides.\n");

    add_item( ({ "pool", "basin", "here", "area", "deep pool",
                 "very deep pool", }),
        "This pool looks to have been eroded by many years of water"
      + " which has fallen from the cliffs high above. It is rather"
      + " filthy, having been defiled by orcs recently.\n");
    add_item( ({ "rock", "rocks", "slimy rocks", "bottom",
                 "side", "sides", "bottom of the pool" }),
        "The bottom and sides of the pool are comprised of rock which"
      + " is coated with slimy filth. You notice a large opening in"
      + " the rock leading west into the side of the cliff.\n");
    add_item( ({ "west", "cliff", "side of the cliff", "opening",
                 "large opening", "opening in the rock",
                 "large opening in the rock" }),
        "Water is flowing through an opening in the rocks leading"
      + " to the west. The opening appears to be very large, though"
      + " that is difficult to judge in these dark waters.\n");
    add_item( ({ "water", "waters", "dark water", "dark waters",
                 "water of the pool" }),
        "Water is all around you here. It is dark and slightly murky"
      + " no doubt due to the defilement left here by the careless"
      + " orcs.\n");
    add_item( ({ "surface", "surface of the pool", "up" }),
        "The surface of the pool is directly above you, shimmering"
      + " in the light of the forest.\n");
    add_item( ({ "filth", "slime", "slimy filth", "slimy refuse",
                 "refuse", "defilement", "bits", "bits of refuse",
                 "small bits", "small bits of refuse" }),
        "It seems quite obvious what this filth is. You do not care"
      + " to investigate the matter any further.\n");


    add_prop(ROOM_M_NO_ATTACK,
        "Combat is impossible while underwater.\n");

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1", "up",
             describe_surface, 5, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest",
                        "down" }),
        "You swim around the bottom of the pool, but aren't able to"
      + " move very far in that direction.\n");
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from beneath the surface of the pool, gasping for breath,"
      + " and crawls out of the water.");
} /* create_del_rimmon */


/*
 * Function name:        do_swim
 * Description  :        allow the player to swim around
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (parse_command(arg, ({}),
        "[in] [to] [into] [through] [the] [large] 'opening'"))
    {
        write("You swim through the opening in the rocks, and emerge"
            + " into a watery area within the cliffs.\n");

        this_player()->move_living("M", 
            DELRIMMON_DIR + "lakeside/caves/pool_bottom", 1, 0);

        tell_room(this_object(), QCTNAME(this_player())
          + " swims through an opening in the rocks and disappears"
          + " to the west.\n", 0);

        this_player()->add_fatigue(-20);

        return 1;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would use command to initiate the"
            + " movement, but since you are a wizard, that will not"
            + " work. Just use direction commands as you would"
            + " on land.\n");
    }

    this_player()->command(arg);
    return 1;
} /* do_swim */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_swim, "enter");
} /* init */
