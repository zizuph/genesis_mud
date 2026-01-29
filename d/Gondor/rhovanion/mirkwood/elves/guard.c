/*
 * Thranduil's Halls.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_STD_DIR + "room";


void 
create_room()
{
    
    set_short("Halls of the Elvenking");
    set_long("\n");

    
	add_item(({"cave", "hall", "hallway", "wide hall", "wide hallway"}),
	    "\n");
    add_item(({"wall", "walls"}),
        "\n");
    add_item(({"ceiling", "up"}),
        "\n");
    add_item(({"floor", "down"}),
        "\n");
    add_item(({"door", "doors", "stone doors", "double doors"}),
        "\n");
    add_item(({"carving", "carvings", "decoration", "decorations"}),
        "\n");
    add_item(({"patterns", "geometric patterns"}),
        "\n");
    add_item(({"stone", "hard stone"}),
        " \n");
    add_item(({"animal", "animals", "animal carving", "animal carvings"}),
        "\n");
    add_item(({"nature", "trees", "flowers"}),
        "\n");
    add_item(({"torch", "torches"}),
        "\n");
    add_item(({"mirkwood", "forest"}),
        "\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    add_exit(MIRKWOOD_DIR + "elves/corridor", "east");
    add_exit(MIRKWOOD_DIR + "elves/dungeon", "west", "@@dungeon@@");
    add_exit(MIRKWOOD_DIR + "elves/river", "down",  "@@river@@");

}

int
river()
{
write("Having pulled open the trapdoor, you slip down into the darkness " +
    "of the rushing waters below.\n");
return 0;
}

int
dungeon()
{
write("You follow the winding stone stairs as they delve deep into " +
    "the darkness of the earth.\n");
return 0;
}