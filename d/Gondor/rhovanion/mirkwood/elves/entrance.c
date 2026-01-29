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
    set_long("You are standing within a massive cave, where each of the " +
        "walls and floors have been delicately finished over centuries " +
        "of attentive care. A wide hallway stretches away to the " +
        "northwest, a massive pair of double doors, fashioned from " +
        "solid stone, stand fast and secure " +
        "immediately to the southeast. Dozens of intricate carvings " +
        "of animals, nature and even geometric patterns decorate every " +
        "inch of the walls and ceiling, breathing life and beauty into " +
        "what would otherwise be cold, hard stone.\n");

    
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

    add_exit(MIRKWOOD_ELFPATH_DIR + "p36", "east");
    add_exit(MIRKWOOD_DIR + "elves/hall", "northeast");
    

}
