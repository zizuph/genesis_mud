/*
 * Innyard of the Prancing Pony
 * Finwe, May 2002
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit "/d/Shire/bree/base_common";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{

    set_short("Inn yard of the Prancing Pony");
    set_long("This is the inn yard and the entrance of the famous " +
        "Prancing Pony inn. It is a large, outdoor, covered yard and " +
        "paved with rounded stones. The yard has three wings that " +
        "extend from the north, south, and east. A wooden gate leads east " +
        "into the stables.\n");
    add_item(({"stables", "horse stables"}),
        "The stables extend to the east. They look large and probably " +
        "full of horses.\n");
    add_item(({"gate", "wooden gate"}),
        "It is large and made of sturdy wood beams. The gate extends " +
        "from partway down the ceiling to the ground.\n");
    add_item(({"pavers", "paving stones", "paver stones", "rounded stones"}),
        "The rounded stones are set into the ground, forming a " +
        "solid surface. They are gray colored, and clean despite " +
        "the traffic.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of a network of beams and solid looking " +
        "planks of wood. The beams run north and south with the planks " +
        "running east and west. Four sturdy posts hold the ceiling up.\n");
    add_item(({"wooden beams", "beams"}),
        "The wooden beems are square and hewn from large trees. They " +
        "have aged to a golden color and support the ceiling of the " +
        "inn yard. The beams run north and south. Smaller ones make " +
        "up the wooden gate leading to the stables.\n");
    add_item(({"wood planks", "planks of wood", "planks"}),
        "The wood planks lay across the wooden beams and make up the " +
        "ceiling. They are smooth looking and are a golden color.\n");
    add_item(({"wooden posts", "posts"}),
        "The wooden posts are rounded and sunk into the ground. They " +
        "are set into the four corners of the yard and hold the ceiling up.\n");

    set_room_tell_time(45+random(37));
    add_room_tell("Some travellers pass by as they enter the inn.");
    add_room_tell("Weary travellers pass you by and go north into the inn.");
    add_room_tell("Some raucous noise echos from the north.");
    add_room_tell("Someone shouts from inside the inn: Barliman! Where's my beer!");
    add_room_tell("A tired servant runs past you.");
    add_room_tell("Someone shouts from inside the inn: Here, here!!");
    add_room_tell("A rousing song echoes from the inn.");
    add_room_tell("Neighing sounds echo from the stables to the east.");
    
    set_add_sky();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
    add_exit(OLD_BREE_DIR + "inn", "north");
    add_exit(TOWN_DIR + "inndining", "south");
//    add_exit(TOWN_DIR + "stable/stable_yard", "east", "@@block_room@@");
    add_exit(TOWN_DIR + "stable/stable_yard", "east");
    add_exit(ROAD_DIR + "broad02", "west");
//    add_exit(OLD_BREE_DIR + "crossing", "west");

    
}

 
void
init()
{   
    ::init();
}

int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("The gate is closed. You cannot enter the stables.\n");
    return 1;
}

