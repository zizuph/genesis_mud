/*
 * Tower in Dol Guldur - /d/Gondor/rhovanion/dolguldur/tower.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Gondor/std/room";

void
create_gondor()
{
    set_short("A broken tower");
    set_long("You are currently inside the broken tower which sits in the " +
        "center of Dol Guldur. The tower is octagonal in shape, and this " +
        "level is in relatively good shape. It appears that someone has " +
        "set up an office of sorts, with a desk and a bookcase, along the " +
        "east wall. There is a stone staircase running along the north " +
        "wall, with one set of stairs going up and another going down " +
        "into a basement. An open set of double doors in the " +
        "southwestern wall leads back out into the rest of the city.\n");

    add_item( ({"desk", "wood desk", "wooden desk"}),
        "This is a wooden desk, and a much nicer piece of furniture than " +
        "you would have expected to see here in the ruins of Dol Guldur. "+
        "It is not only well constructed, but the wood has been polished " +
        "and it is covered in beautiful scrollwork around the edges.\n");
    add_item( ({"wall", "walls"}),
        "The walls of the tower are made up of large blocks of stone.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling of the tower has strong wooden beams supporting " +
        "large slabs of stone.\n");
    add_item( ({"down", "floor"}),
        "The floor of the tower is made up of large slabs of stone.\n");
    add_item( ({"chair", "wood chair", "wooden chair", "throne",
            "wood throne", "wooden throne"}),
        "A large chair, carved from a single piece of wood, is pushed " +
        "up against the desk. Like the desk, it is polished and decorated " +
        "with scrollwork, making it look more like a throne than a simple " +
        "chair.\n");
    add_item( ({"door", "doorway", "doors", "double doors"}),
        "The double doors that sit in the southwestern wall are flung " +
        "open, leading to the ruins of Dol Guldur beyond.\n");
    add_item( ({"office", "office space", "space"}),
        "It appears that someone has cleared out some space to make an " +
        "office here. A small bookcase has been pushed up against the " +
        "eastern wall, while a magnificent looking desk and chair stand " +
        "in front of it.\n");
    add_item( ({"bookcase", "bookshelf", "small bookcase", "small bookshelf",
            "wooden bookcase", "wooden bookshelf"}),
        "This bookcase is not very large, but it seems to be more than " +
        "adequate for the person using it. The construction is quite " +
        "good, although not nearly so nice as the desk and chair.\n");
    add_item( ({"stair", "stairs", "staircase", "stone stair", "stone stairs",
            "stone staircase"}),
        "These stairs appear to be made of stone, but it is hard to see " +
        "much more than that as large chunks of rubble seem to be " +
        "covering them.\n");
    add_item( ({"stone", "stones"}),
        "There is a lot of stone here, what exactly did you want to look " +
        "at?\n");
    add_item( ({"rubble", "chunk", "chunks", "large chunk", "large chunks",
            "chunk of stone", "chunks of stone", "large chunks of stone",
            "large chunk of stone", "large chunks of rubble",
            "large chunk of rubble", "chunks of rubble", "chunk of rubble"}),
        "Several large chunks of stone fill the staircase, it would be " +
        "almost impossible for anyone to go either up or down until they " +
        "have been cleared.\n");
    add_item( ({"slab", "slabs", "stone slab", "stone slabs", "slab of stone",
            "slabs of stone", "large slab", "large slabs", "large stone slab",
            "large stone slabs", "large slab of stone", 
            "large slabs of stone"}),
        "These large slabs of stone are still in very good condition, and " +
        "they make up both the ceiling and floor here.\n");
    add_item( ({"block", "blocks", "large block", "large block of stone",
            "large blocks", "large blocks of stone"}),
        "The walls are very strong and stout here, having been constructed " +
        "from these large blocks of stone. The mortar between the blocks " +
        "is still in good condition, keeping this level of the tower " +
        "solidly intact.\n");
    add_item( ({"mortar", "cement"}),
        "There is some mortar between the blocks of stone in the walls " +
        "here, still in very good condition.\n");
    add_item( ({"wood", "wooden"}),
        "There are a couple things made of wood here. A desk, a chair and " +
        "even a bookcase. Which one did you want to look at?\n");
    add_item( ({"tower", "broken tower", "tall tower", "ruined tower"}),
        "You are currently inside the tower, in the heart of Dol Guldur.\n");

    add_npc(DG_DIR + "npc/azkhnaur");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(DG_DIR + "main3", "southwest", 0, 0, 0);

    set_no_exit_msg( ({"north", "northeast", "east", "southeast", "south", 
            "west", "northwest"}),
        "There is no exit from the tower in this direction, and the " +
        "walls here are very solid.\n");
    set_no_exit_msg( ({"up", "down"}),
        "You try to get through the blocks of rubble filling the stairs, " +
        "but you have no success. You will have to wait until someone " +
        "clears them away.\n");

    reset_room();

}