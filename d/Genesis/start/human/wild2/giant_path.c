/*
 * 	giant_path.c			Styles.   3 Mar 1993
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

    set_short("Giant path");
    set_long("You are wandering along a wide mountain trail that climbs " +
        "up deeper into the rocky heights of the Grey Mountains, leading " +
        "to a small plateau at the western edge of the valley. The valley " +
        "itself is small, but full of tall green grass and bright " +
        "wildflowers that spread out to the south and east. The broken " +
        "peaks of the Grey Mountains surround the valley, the rocky " +
        "cliffs preventing easy travel for anyone who might stray off " +
        "the trail.\n");

    add_trees(1);

    add_exit(THIS_DIR + "giant_conf","west");
    add_exit(THIS_DIR + "grove","east");

    set_no_exit_msg(({"northeast","north","northwest","southwest","south",
            "southeast"}),
        "The rocky cliffs that make up the steep mountainsides here " +
        "prevent you from going in that direction. You will have to find " +
        "another way around.\n");

    add_item(({"foothill","foothills","rugged foothills","rugged foothill",
            "hill","hills"}),
        "You are in the foothills of the Grey Mountains, overlooking a " +
        "small valley that spreads out to the east. The " +
        "rugged foothills slope steadily upwards all around, rising " +
        "up into rocky cliffs.\n");
    add_item(({"mountain","mountains","grey mountains","mountainside",
            "mountainsides"}),
        "The Grey Mountains rise up all around you here, surrounding " +
        "the small valley before you. The rocky mountainside is " +
        "filled with steep cliffs and rugged foothills that make " +
        "travel away from the trail almost impossible.\n");
    add_item(({"vale","valley","small valley"}),
        "Stretching out to the east, a small valley full of " +
        "tall grasses and colourful wildflowers spreads out before " +
        "you.\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "The trail seems to lead towards a small plateau to the west while " +
        "leading down deeper into the valley to the east. The trail " +
        "has obviously seen recent use as there are some very big " +
        "footprints clearly visible in the dirt.\n");
    add_item(({"footprints","giant footprints","big footprints",
            "footprint","giant footprint","big footprint"}),
        "These footprints are very, VERY big! You have trouble imagining " +
        "how big someone would have to be to leave footprints this large.\n");
    add_item(({"plateau","small plateau"}),
        "There is a small plateau on the west side of the valley, the trail " +
        "you are on seems to lead to the top of it.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}