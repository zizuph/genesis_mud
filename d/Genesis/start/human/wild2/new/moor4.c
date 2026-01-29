/*      moor4.c
 *
 *  This is a hastily constructed room meant to extend certain roads
 *  and make Style's map consistent with the actual room layouts.
 *  (Gorboth, May 2010)
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

void
create_wild_room()
{
    set_items_sparkle();
    set_items_moor();
    set_herbs();

    set_short("Misty moor");
    set_long("You are on the eastern edge of the moors on the coast of " +
        "the Pen Sea. To the west, small groves of trees and large " +
        "patches of wildflowers grow in the long green grasses. A " +
        "heavy mist settles around the low hills of the moors, making " +
        "it difficult to see very far. The heavy waves of the Pen Sea " +
        "crash against the shore, rolling up along the sandy beaches. The " +
        "stone path you are on follows a peninsula that juts east out " +
        "into the sea, while not far to the south, you can see the " +
        "walls of Sparkle protruding out into the water.\n");

    add_trees(0);

    add_exit(THIS_DIR + "peninsula", "east");
    add_exit(THIS_DIR + "moor3", "west");
    add_exit(THIS_DIR + "moor4","southeast","@@sea@@",1,1);
    add_exit(THIS_DIR + "moor4","northwest","@@moor@@",1,1);
    add_exit(THIS_DIR + "moor4","northeast","@@sea@@",1,1);
    add_exit(THIS_DIR + "moor4","north","@@sea@@",1,1);
    add_exit(THIS_DIR + "n_shore","southwest",0,1,1);
    add_exit(THIS_DIR + "moor4","south","@@sea@@",1,1);

    add_item(({"sparkle","walls","wall","wooden walls","wooden wall",
            "stockade","wooden stockade"}),
        "To the south, you are able to see the wooden walls of the " +
        "stockade that surrounds Sparkle, jutting out into the " +
        "blue waters of the Pen Sea.\n");
    add_item(({"peninsula","beach","sandy beach","sand"}),
        "A long sandy beach has been created where the Pen Sea brushes " +
        "up against the moors here. The beach stretches out from the " +
        "walls of Sparkle just visible to the south and around a " +
        "peninsula that extends to the east before trailing off in the " +
        "distance to the north.\n");
    add_item(({"sea","coast","shore","pen sea","water","waters","waves",
            "wave"}),
        "You can see the choppy waves of the Pen Sea rolling up a sandy " +
        "beach to the southeast.");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        moor
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the moors in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
moor()
{
    write("You attempt to leave the stone path to make your own way across " +
        "the moors, but you find that the land here is too wet here. You " +
        "will have to try to find an alternative route.\n");
    return 1;
}
/* moor */

/*
 * Function name:        sea
 * Description  :        Provides an explanation why a mortal cannot move
 *                       into the sea
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
sea()
{
    write("You take a step into the rolling waves of the Pen Sea that " +
        "are crashing up against the shore. It seems obvious that you " +
        "cannot go any further in this direction.\n");
    return 1;
}
/* sea */