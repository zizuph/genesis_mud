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

    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1", "north");
    set_distance("north", 1);
    add_exit("far_west3", "northeast");
    set_distance("northeast", 1);
    add_exit("west4", "east");
    set_distance("east", 1);
    add_exit("west4", "southeast");
    set_distance("southeast", 1);
    add_exit("far_west4", "south");
    set_distance("south", 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore3", "southwest");
    set_distance("southwest", 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore4", "west");
    set_distance("west", 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5", "northwest");
    set_distance("northwest", 1);
} /* create_nen_hithoel */
