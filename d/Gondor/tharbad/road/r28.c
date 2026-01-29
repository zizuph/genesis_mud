/*
 *      /d/Gondor/tharbad/road/r28.c
 *
 *      Coded by Zephram.
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// How hard is it to climb the slope?
#define HARD_TO_CLIMB  4 

public int     climb();

public void
create_roads() 
{
    set_street("overgrown stone road");
    set_where("northwest");
    set_county("Tharbad");
    set_land("old Cardolan");
    set_mountain("Greyflood slopes");
    set_vegetation("green holly and rosebushes");
    set_extraline("The road is running through the ruins of a small "
        + "village here. Scattered green holly and rosebushes grow "
        + "between the ruins. The road is made of cracked and "
        + "slippery paving stones and climbs out of the ruins to the "
        + "northwest. To the southeast, it crosses a small open "
        + "space before coming to a river and more ruins.");

    add_exit(THARBAD_DIR + "ford/f04", "southeast", climb, 7);
    add_exit(CARD_DIR    + "road/r29", "northwest", climb, 7);

    add_item("road", BSN("The road once was wide and the paving stones "
        + "still show the workmanship of its builders, but now it is "
        + "covered with rubble from the ruins of the village. It is "
        + "climbing out of the village to the northwest, up a steep "
        + "slope, while in the other direction it is running towards "
        + "the ruins visible on the bank of the river."));
    add_item( ({ "river", "greyflood", "bank", }), BSN("The river "
        + "flows about a mile to the southeast. On the bank of the "
        + "river, more ruins can be seen, and in the river, there "
        + "is a small narrow island."));
    add_item( ({ "island", "bridge", }), BSN("In the middle of the "
        + "river, there is a narrow island, and on the island rises "
        + "a wide ruined pillar. which once may have supported a "
        + "bridge crossing the river, but that bridge must have been "
        + "destroyed long ago."));
    add_item( ({"ruin", "ruins", "village", "stone", "stones"}),
        BSN("Only the foundations of the huts, built of scavenged "
            + "stone and brick, are visible in the ruins of the "
            + "village. Everything seems to have been looted and "
            + "destroyed several times after the inhabitants "
            + "deserted the village."));
    add_item( ({"bush","bushes","rosebush","rosebushes","holly"}),
        "A few scrubby bushes cling to the bank and ruins here.\n");
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
        write("You stumble over a huge stone block.\n");
        say(QCTNAME(TP) + " stumbles.\n");
        return 1;
    }
   
    write("You climb over the huge blocks of stone and masonry.\n");
    return 0;
}

