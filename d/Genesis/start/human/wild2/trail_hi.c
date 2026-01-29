/*
 * 	trail_hi.c			Styles.   3 Mar 1993
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

    set_short("Upper part of a trail");
    set_long("You are wandering along a wide mountain trail that climbs " +
        "up towards a geyser at the west end of the trail before falling " +
        "back down to the lush valley east of here. The small valley is " +
        "full of tall green grass and bright wildflowers that sway in the " +
        "mountain breeze. The mountainside is full of rocky cliffs and " +
        "rugged foothills, as all around you, the Grey Mountains frame " +
        "the horizon with their broken, jagged peaks. It appears that " +
        "the only safe passage you can find is to follow the trails that " +
        "wind and twist their way through the mountains.\n");

    add_trees(0);

    add_exit(THIS_DIR + "geyser","west");
    add_exit(THIS_DIR + "trail_lo","east");

    set_no_exit_msg(({"northeast","southwest","southeast","north","south",
            "northwest"}),
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
        "The trail seems to lead towards a geyser to the west while " +
        "leading down deeper into the valley to the east.\n");
    add_item(({"geyser","hole"}),
        "There appears to be a geyser at the end of the trail just west " +
        "of here.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}