/*
 * 	stockade.c			Styles.   3 Mar 1993
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

    set_short("By the stockade");
    set_long("You are standing near a tall wooden stockade, north of the " +
        "village of Sparkle, sitting on the edge of the moors. The woodwork " +
        "is tall, strong and well built, obviously designed to prevent " +
        "anyone entering the city from this direction. A small stream " +
        "winds past, cutting between you and the city walls as it wanders " +
        "east towards the Pen Sea. A path of fieldstones rests on the " +
        "wet ground of the moors, following the stream to both the " +
        "west and east, in addition to travelling north deeper into " +
        "the dense mists that surround the low hills of the moorlands.\n");

    add_trees(0);

    add_exit(THIS_DIR + "moor2","north");
    add_exit(THIS_DIR + "stream3","west");
    add_exit(THIS_DIR + "n_shore","east");
    add_exit(THIS_DIR + "moor3","northeast",0,1,1);
    add_exit(THIS_DIR + "stockade","southwest","@@stream@@",1,1);
    add_exit(THIS_DIR + "stockade","southeast","@@stream@@",1,1);
    add_exit(THIS_DIR + "stockade","south","@@stream@@",1,1);
    add_exit(THIS_DIR + "stockade","northwest","@@moor@@",1,1);

    add_item(({"stream","small stream" }),
	    "This small stream runs merrily east towards the Pen Sea, " +
        "bordered a stone path on one side and a wooden stockade " +
        "on the other.\n");
    add_item(({"stockade","walls","wooden walls","wooden stockade","wood",
            "city walls","city wall","wall","wooden wall","tall wall",
            "sparkle","city","town","village"}),
	    "The stockade is a sturdy wooden wall that surrounds the " +
        "legendary city of Sparkle. It is rather tall, and the wooden " +
        "posts are sharpened into stakes, discouraging anyone from " +
        "trying to climb over.\n");
    add_item(({"stake","post","stakes","posts","wooden post","wooden posts",
            "wooden stake","wooden stakes"}),
	    "These tall wooden posts are very sharp at the top, all lashed " +
        "together to form a wall, discouraging anyone who might attempt " +
        "to climb over.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the southeast.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the south.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "The tall wooden stockade that surrounds Sparkle blocks your " +
        "view to the southwest.\n");

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
 * Function name:        stream
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the stream in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
stream()
{
    write("You don't think you could swim across the stream, especially " +
        "since there is a tall wooden wall on the other side!\n");
    return 1;
}
/* stream */