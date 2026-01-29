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
    set_currentstr(NEAR_MID_CURRENT);
    set_depth(NEAR_MID_DEPTH);

    add_exit("east1", "north");
    set_distance("north", 1);
    add_exit("far_east2", "east");
    set_distance("east", 1);
    add_exit("far_east3", "southeast");
    set_distance("southeast", 1);
    add_exit("east3", "south");
    set_distance("south", 1);
    add_exit("mid3", "southwest");
    set_distance("southwest", 1);
    add_exit("mid2", "west");
    set_distance("west", 1);
    add_exit("mid1", "northwest");
    set_distance("northwest", 1);
} /* create_nen_hithoel */
