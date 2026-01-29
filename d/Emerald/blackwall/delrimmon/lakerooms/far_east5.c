#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/on_lake";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name:        create_nen_hitoel
 * Description  :        set up the lake room
 */
public void
create_nen_hithoel()
{
    set_show_area_desc();
    set_loc(5);
    set_extraline("This is just a place holder, but it works!");

    /* water stuff */
    set_downstreamdir("south");
    set_upstreamdir("north");
    set_currentstr(SIDE_CURRENT);
    set_depth(SIDE_DEPTH);

    add_exit("east4", "north");
    set_distance("north", 1);
    add_exit("far_east4a", "northeast");
    set_distance("northeast", 1);
    add_exit("far_east6", "southwest");
    set_distance("southwest", 1);
    add_exit("east5", "west");
    set_distance("west", 1);
    add_exit("east4", "northwest");
    set_distance("northwest", 1);

    set_no_exit_msg( ({ "east", "southeast", "south" }),
        "Walls of rock rise out of the water in that direction,"
      + " preventing your movement.\n");
} /* create_nen_hithoel */
