/* 
 *	field11.c			Styles.   3 Mar 1993
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
    set_items_field();
    set_items_darkroad();
    set_herbs();
    
    set_short("Dark Road");
    set_long("You have reached a bend in the dark road, as it travels " +
        "south towards Sparkle and now turns west, skirting base of the " +
        "Grey Mountains as it wanders up towards the northern lands. A " +
        "peculiar path paved with yellow bricks dives through a shallow " +
        "pass through the mountains to the north. Wide grassy fields, " +
        "liberally sprinkled with wildflowers, cover the valley to the " +
        "south and west, while heavy mists have fallen across the wet " +
        "moorlands than stretch out to the east before meeting up " +
        "with the shining blue Pen Sea that covers the eastern horizon.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field10","west",0, 0);
    add_exit(THIS_DIR + "field7","south",0, 0);
    add_exit("/d/Genesis/start/dwarf/lvl2/road2","north",0);
    add_exit(THIS_DIR + "field11", "northeast", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "field11", "southeast", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "field11", "east", "@@moor@@", 1,1);
    add_exit(THIS_DIR + "field11", "northwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "ruin", "southwest", 0,1,1);

    add_item(({"moor", "moors", "moorland"}),
        "The gentle green foothills of the Grey Mountains turn into " +
        "a misty moorland as they flatten out to the east. There are " +
        "two bridges you can see that can take you across the river " +
        "to the heart of the moorlands.\n");
    add_item(({"mist","mists"}),
        "Dense mists swirl and settle across the vast moorlands that "  +
        "stretch out to the east.\n");
    add_item(({"pass","mountain pass","shallow pass"}),
        "This mountain pass is rather shallow, providing easy access " +
        "to the north. What is most peculiar about this pass is that " +
        "the path through it is paved with bricks painted yellow to " +
        "look like gold!\n");
    add_item(({"path","yellow brick road","peculiar path"}),
        "How peculiar! It looks like someone has paved this path with " +
        "bricks painted yellow, in order to make them look like gold! " +
        "You have heard that this is the path to Dwarfheim the " +
        "traditional dwarven homeland in the north.\n");
    add_item(({"brick","bricks","yellow brick","yellow bricks"}),
        "These bricks have been painted yellow in order to make them " +
        "look like gold! This is how the dwarves remind their human " +
        "friends from Sparkle that a great wealth flows down from " +
        "Dwarfheim.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        moors
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the moorlands in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
moor()
{
    write("Dense mists swirl across the wet moors that begin east of the " +
        "Dark Road. There does not appear to be a safe way to enter the " +
        "moors in this direction.\n");
    return 1;
}
/* moor */

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
mount()
{
    write("In order to go in that direction, you would need to have the " +
        "skills of an expert mountain climber. It looks like you will have " +
        "to go in another direction for now.\n");
    return 1;
}
/* mount */