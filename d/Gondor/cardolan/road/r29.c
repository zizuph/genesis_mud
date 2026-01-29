/*
 *      /d/Gondor/cardolan/road/r29.c
 *
 *      Coded by Zephram.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 *	15-Feb-1997, Olorin: added skill check for going se.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// How hard is it to climb the slope?
#define HARD_TO_CLIMB  6

public int     climb();

public void
create_roads() 
{
    set_street("grass-covered road");
    set_where("southeast");
    set_county("Cardolan");
    set_land("Eriador");
    set_mountain("Greenway slopes");
    set_vegetation("occasional oak tree and tall yellow grass");
    set_extraline("You are on a treelined road which is overgrown with tall grass."
        + " Looking around you see the occasional oak tree and tall yellow grass "
        + "covering the land of Cardolan. The road runs down a steep slope from "
        + "the central plains southeast toward the distant city of Tharbad.");
    add_item(({"block", "blocks", "stone block", "huge stone block"}),
        "You see some very large stone blocks on the path that leads down the " +
        "slope to the southeast. Perhaps you should think twice about trying " +
        "to climb over them.\n");
    add_exit(CARD_DIR    + "road/r36", "northwest",     0, 3);
    add_exit(THARBAD_DIR + "road/r28", "southeast", climb, 3);
}

public int
climb()
{   
    int     climb_try = (HARD_TO_CLIMB / 2),
            skill     = TP->query_skill(SS_CLIMB);

    climb_try += random(climb_try) + 1;

    if (skill < climb_try)
    {
        TP->reduce_hit_point(climb_try - skill);
        write("When you try to climb down the slope, you stumble over a huge stone block.\n");
        say(QCTNAME(TP) + " stumbles.\n");
        return 1;
    }
   
    write("You walk down the slope, climbing over huge blocks of stone and masonry.\n");
    return 0;
}

