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
    set_currentstr(MIDDLE_CURRENT);
    set_depth(MIDDLE_DEPTH);

    add_exit("mid4", "north");
    set_distance("north", 1);
    add_exit("east4", "northeast");
    set_distance("northeast", 1);
    add_exit("east5", "east");
    set_distance("east", 1);
    add_exit("east5", "southeast");
    set_distance("southeast", 1);
    add_exit("mid6", "south");
    set_distance("south", 1);
    add_exit("west6", "southwest");
    set_distance("southwest", 1);
    add_exit("west5", "west");
    set_distance("west", 1);
    add_exit("west4", "northwest");
    set_distance("northwest", 1);
} /* create_nen_hithoel */
