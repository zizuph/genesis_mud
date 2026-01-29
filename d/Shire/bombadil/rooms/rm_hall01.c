/*
 * Downstairs west hall of Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("The west hallway");
    set_long("This is the west end of the hallway in the house. " +
        "It's rather plain except for the lamps hanging from the " +
        "ceiling and the hardwood floor. A long carpet runs the " +
        "length of the hall, adding warmth and comfort to the " +
        "hallway.\n");
    add_item(({"carpet"}),
        "The carpet is long and rectangular. It is the length of " +
        "the hallway with a white fringe on both ends. The carpet " +
        "is a soft blue color with abstract flower designs.\n");
    add_item(({"flower designs", "abstract flower designs", "designs"}),
        "The abstract flower designs are suggestive of water " +
        "lilies surrounded by twining ivy.");
    remove_item(({"candles", "candle"}));

    reset_shire_room();

    add_exit(ROOMS_DIR + "rm_kitchen", "south");
    add_exit(ROOMS_DIR + "rm_hall02", "east");
    add_exit(ROOMS_DIR + "rm_main",  "west", );
}


void
reset_shire_room()
{
}
