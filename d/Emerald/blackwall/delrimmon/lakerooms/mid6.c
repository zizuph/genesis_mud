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

    add_exit("mid5", "north");
    set_distance("north", 1);
    add_exit("east5", "northeast");
    set_distance("northeast", 1);
    add_exit("east6", "east");
    set_distance("east", 1);
    add_exit("east7", "southeast");
    set_distance("southeast", 1);
    add_exit("west7", "southwest");
    set_distance("southwest", 1);
    add_exit("west6", "west");
    set_distance("west", 1);
    add_exit("west5", "northwest");
    set_distance("northwest", 1);

    set_no_exit_msg( ({ "south" }),
        "Ael Rannath rises directly out of the water to the south,"
      + " its rock walls preventing movement in that direction.\n");
} /* create_nen_hithoel */
