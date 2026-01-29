/*
 * 	grove.c			Styles.   3 Mar 1993
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

    set_short("In a small grove");
    set_long("The path you are following has led you into the middle of " +
        "a small grove of trees on the east side of a small mountain " +
        "valley. You can see the tall green grass of the valley swaying " +
        "with every gust of wind that falls down from the jagged peaks " +
        "of the Grey Mountains. Dozens of vividly coloured wildflowers " +
        "peek out from behind the grasses, enhancing the beautiful " +
        "vista spread out before you. A small path climbs through " +
        "the mountains to the east towards a very large tree, while " +
        "widening into two larger trails that dive down in the valley " +
        "to the south and the west.\n");

    add_trees(1);

    add_exit(THIS_DIR + "giant_path","west");
    add_exit(THIS_DIR + "trail_lo","south");
    add_exit(THIS_DIR + "big_tree","east");
    add_exit(THIS_DIR + "grove", "southwest","@@hill@@",1,1);
    add_exit(THIS_DIR + "grove", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "grove", "northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "grove", "north","@@mount@@",1,1);
    add_exit(THIS_DIR + "grove", "northeast","@@mount@@",1,1);

    add_item(({"trees","tree","grove"}),
        "This grove is filled with dozens of trees, mostly maples, oaks " +
        "and fir trees.\n");
    add_item(({"oak trees","oak tree","oak","oaks"}),
        "Tall and strong, these oak trees tower above the other trees " +
        "in the grove.\n");
    add_item(({"fir trees","fir tree","fir","firs"}),
        "There are plenty of fir trees surrounding you here, their " +
        "prickly evergreen needles scratching you as you walk past.\n");
    add_item(({"maple trees","maple tree","maple","maples"}),
        "Several strong maple trees are growing between the firs and " +
        "oaks in this grove, their leafy branches famous for the " +
        "beautiful colours they display in the autumn.\n");
    add_item(({"vale","valley","small valley"}),
        "Stretching out to the south and west, a small valley full of " +
        "tall grasses and colourful wildflowers spreads out before " +
        "you.\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "A small dirt path winds up and out of the grove to the east " +
        "while splitting into two wider trails that pass through the " +
        "valley to the west and the south.\n");
    add_item(({"large tree","massive tree","huge tree"}),
        "You can see a massive tree reaching up into the air just east " +
        "of the grove. You could probably inspect it up close if you " +
        "followed the small path that leads east.\n");
    add_item(({"rock","rocks","cliff","rocky cliff","cliffs","rocky cliffs",
                "steep cliff","steep cliffs","wall","walls","cliff wall",
                "cliff walls","rocky cliff wall","rocky cliff walls"}),
        "There are rocky cliff walls that begin to rise up around the " +
        "path as it cuts east through the mountains.\n");
    add_item(({"foothill","foothills","rugged foothills","rugged foothill",
            "hill","hills"}),
        "You are in the foothills of the Grey Mountains, overlooking a " +
        "small valley that spreads out to the south and west. The " +
        "rugged foothills slope steadily upwards to the east, rising " +
        "up into rocky cliffs.\n");
    add_item(({"mountain","mountains","grey mountains","mountainside",
            "mountainsides"}),
        "The Grey Mountains rise up all around you here, surrounding " +
        "the small valley before you. The rocky mountainside is " +
        "filled with steep cliffs and rugged foothills that make " +
        "travel away from the trails almost impossible.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("The rocky cliffs that make up the steep mountainsides here " +
        "prevent you from going in that direction. You will have to find " +
        "another way around.\n");
    return 1;
}
/* mount */

/*
 * Function name:        hill
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the hills in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
hill()
{
    write("You attempt to cross the valley to the southwest, but you find " +
        "that the rocky slope of the hill before you is too unstable. You " +
        "will have to use the trail leading south instead.\n");
    return 1;
}
/* hill */