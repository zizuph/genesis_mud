/*
 * Kitchen in the vampire manor
 * Louie 2006
 */ 
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("kitchen");
    set_long("This is the kitchen of the manor.  "+
        "The room is roughly square, with bare stone walls.  "+
        "A large oven and open fire pit are along the east wall, "+
        "while a long wooden table rests against the north wall.  "+
        "A rack holding various utensils runs along the wall above "+
        "the table.  Empty shelves occupy what free space there "+
        "is along the south wall.  "+
        "\n");

    add_exit("dining.c", "west");
    add_exit("storageroom.c", "southwest");

    add_item(({"west","dining","dining room" }),
        "To the west is the dining room of the manor.\n");

    add_item(({"kitchen"}),
        "You are standing in the kitchen of the manor.  "+
        "Once upon a time it may have been bustling with "+
        "activity, but now it is empty and quiet.\n");

    add_item(({"southwest","storage","storage room"}),
        "To the southwest is the storage room for the kitchen.\n");

    add_item(({"rack","utensils","various utensils"}),
        "The rack above the table holds various mundane cooking "+
        "utensils used in the preparation of meals.\n");

    add_item(({"shelves","empty shelves"}),
        "The shelves along the south wall may have once held "+
        "items or foods used by the manor cook, but they are "+
        "completely empty now.\n");

    add_item(({"table","long table","wooden table","long wooden table"}),
        "The long wooden table was one used as both a preparation "+
        "area and chopping block.  It is now completely cleaned and "+
        "apparently unused.\n");

    add_item(({"oven","iron oven","contraption","iron contraption",
        "large iron contraption"}),
        "The oven is a large iron contraption once used for "+
        "baking.  It looks clean and unused.\n");

    add_item(({"pit","fire pit"}),
        "The fire pit appears to have not been used for a "+
        "long time.  In the past it would have been used to "+
        "cook and roast various meals.\n");

    add_item(({"walls","wall","east wall","north wall","south wall",
        "bare walls","stone walls","bare stone walls"}),
        "The oven and fire pit are near the east wall, "+
        "while the table is along the north wall.  "+
        "Empty shelves line the south wall.  "+
        "\n");


}

