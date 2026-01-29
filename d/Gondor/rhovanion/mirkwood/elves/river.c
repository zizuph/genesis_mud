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
    
    set_short("Forest river");
    set_long("It is so completely dark in here that you cannot see " +
        "a thing! The water is rather cold and is battering you " +
        "against rough stone walls. There seems to be no way out " +
        "aside from drowning. Blub... blub... blub... " +
        "If you are a wizard, go somewhere else - else, ask " +
        "Varian to transport you out.\n");

    
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
    add_prop(ROOM_I_LIGHT,0);


}


