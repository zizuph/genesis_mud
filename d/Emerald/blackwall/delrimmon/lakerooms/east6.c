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

    add_exit("east5", "north");
    set_distance("north", 1);
    add_exit("far_east5", "northeast");
    set_distance("northeast", 1);
    add_exit("far_east6", "east");
    set_distance("east", 1);
    add_exit("east7", "south");
    set_distance("south", 1);
    add_exit("mid6", "west");
    set_distance("west", 1);
    add_exit("mid5", "northwest");
    set_distance("northwest", 1);

    set_no_exit_msg( ({ "southwest" }),
        "The tall rock walls of Ael Rannath rise from the water to"
      + " the southwest, blocking your movement.\n");
} /* create_nen_hithoel */
