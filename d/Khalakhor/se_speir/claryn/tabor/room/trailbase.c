/*
 * trail_1.c
 *
 * This is part of the trail north of Tabor Sogh.
 *
 * Khail - Jan 9/98
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

string *herbs = HERBMASTER->query_herbs(({TERRAIN_PLAIN,}));

public void
reset_room()
{
    set_searched(1);
}

public void
create_trail()
{
    set_short("on a grassy trail");
    set_long("   You are on a lightly trampled grassy trail leading " +
        "down into the little fishing village Tabor Sogh, " +
        "perched at the edge of Lear Min, the great sea between " +
        "southeastern and southwestern arms of Khalakhor. " +
        "Low, grass-covered hills surround the village on all " +
        "sides, bathing the grey stone buildings in an almost " +
        "green glow as the sun shines off the lush surroundings.\n");

    BEES; // bees from bk_treeX will follow victim into trail rooms

    add_item(({"trail"}),
        "The trail you are on is little more than a lightly " +
        "trampled footpath in the grass.\n");
    add_item(({"town","village","tabor sogh","Tabor Sogh"}),
        "Tabor Sogh is an old fishing village, but has never " +
        "grown much beyond a handful of homes and a few " +
        "necessities for fishing. The village consists of " +
        "a single road upon which all buildings are built " +
        "of dark grey stone.\n");
    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick grey clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "grey clouds",
        "thick grey clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"ground","grass"}),
        "The grass here has been lightly trampled, but still " +
        "appears to have seen little enough traffic to cover " +
        "the earth beneath.\n");
    add_item(({"buildings","stone buildings","low buildings"}),
        "A number of buildings occupy the village, most " +
        "look pretty much identical with stone walls and " +
        "thatched roofs.\n");
    add_item(({"wall","walls"}),
        "The walls of all the buildings are are made " +
        "in a similar fashion, of dark grey stone " +
        "but are too far away for you to see any more detail.\n");
    add_item(({"shore","shoreline"}),
        "Between the village and the sea, a thin strip of pebbly " +
        "shore stands out as a stark border between the grey-blue " +
        "water and green grass.\n");
    add_item(({"water","sea","Lear Min","lear min"}),
        "The waters of Lear Min are are slate grey in colour, " +
        "with white caps topping the larger of the waves in " +
        "the choppy waters as far as the eye can see.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PLAIN);

    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"grass","here"}),2);

    reset_room();
}

