/*
 * 	trail_lo.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

void
create_wild_room()
{
    set_items_sparkle();
    set_herbs();

    set_short("Lower part of a trail");
    set_long("You are wandering along a wide mountain trail that climbs " +
        "up deeper into the rocky heights of the Grey Mountains to the " +
        "west. A small valley full of tall green grass and bright " +
        "wildflower spreads out below you, a small grove of trees " +
        "growing at the northern end. All around you, the Grey " +
        "Mountains frame the horizon with their broken peaks, " +
        "completely enclosing the valley leaving you few options " +
        "but to follow the trails if you want to move around safely.\n");

    add_trees(1);

    add_exit(THIS_DIR + "grove","north");
    add_exit(THIS_DIR + "trail_hi","west");

    set_no_exit_msg(({"northwest"}),
        "You attempt to cross the valley to the northwest, but you find " +
        "that the rocky slope of the hill before you is too unstable. You " +
        "will have to use the trail leading north instead.\n");
    set_no_exit_msg(({"northeast","southwest","southeast","east","south"}),
        "The rocky cliffs that make up the steep mountainsides here " +
        "prevent you from going in that direction. You will have to find " +
        "another way around.\n");

    add_item(({"foothill","foothills","rugged foothills","rugged foothill",
            "hill","hills"}),
        "You are in the foothills of the Grey Mountains, overlooking a " +
        "small valley that spreads out to the north. The " +
        "rugged foothills slope steadily upwards to the east, rising " +
        "up into rocky cliffs.\n");
    add_item(({"mountain","mountains","grey mountains","mountainside",
            "mountainsides"}),
        "The Grey Mountains rise up all around you here, surrounding " +
        "the small valley before you. The rocky mountainside is " +
        "filled with steep cliffs and rugged foothills that make " +
        "travel away from the trail almost impossible.\n");
    add_item(({"vale","valley","small valley"}),
        "Stretching out to the north, a small valley full of " +
        "tall grasses and colourful wildflowers spreads out before " +
        "you.\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "The trail you are on climbs higher into the mountains to the " +
        "west while leading across the small valley to the north.\n");
    add_item(({"trees","tree","grove"}),
        "A small grove of trees grows at the northern end of the valley.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}