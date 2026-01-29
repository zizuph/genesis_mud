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
    set_extraline(
        "The waters spread out magnificently to the north,"
      + " running a great distance towards towering cliffs"
      + " which frame the horizon in the distance. Just to the"
      + " south, a green lawn runs along the lakeshore upon the"
      + " feet of Melan Rath.");

    /* water stuff */
    set_downstreamdir("east");
    set_upstreamdir( ({ "northwest", "north" }) );
    set_currentstr(SIDE_CURRENT);
    set_depth(SIDE_DEPTH);

    set_shore_desc(
        "Just to the south, the waters of the lake lap quietly"
      + " against the banks of a green lawn which rests before the"
      + " feet of Melan Rath.");

    add_exit("west5", "north");
    set_distance("north", 1);
    add_exit("west5", "northeast");
    set_distance("northeast", 1);
    add_exit("west6", "east");
    set_distance("east", 1);
    add_exit("west7", "southeast");
    set_distance("southeast", 1);
    add_exit(DELRIMMON_DIR + "lakeside/parth1", "south");
    set_distance("south", 1);
    add_exit(DELRIMMON_DIR + "lakeside/parth2", "southwest");
    set_distance("southwest", 1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore1", "west");
    set_distance("west", 1);
    add_exit("far_west5", "northwest");
    set_distance("northwest", 1);
} /* create_nen_hithoel */
