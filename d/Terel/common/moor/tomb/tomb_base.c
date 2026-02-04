// Base room for the tomb area
// Lilith Jan 2022 
//  Revisions:
//  Lilith, Mar 2022: removed terrain

#include "/d/Terel/include/Terel.h"
inherit "/std/room";
#include "../local.h"
//#include "/sys/terrain.h"

// This is a tomb, only the dead are welcome.
public mixed
teleport_test()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
        return 0;    
	else
        return "This is no place for the living!\n";	
}

int 
test_exit()
{
    object zombie = present("zombie", TO);
    
	if (zombie)
	{
        if (random(3) == 0)
		{
            write("The "+ zombie->short() +" prevents you from going in "+
                "that direction.\n");
			say(QCTNAME(zombie) + " stops " + QTNAME(TP) +" from leaving.\n", 
                ({ TP, zombie }));
            return 1;
		}
	else return 0;
	}
	
	return 0;
}

void
add_tomb_items()
{
    add_item("air", "It is so foul its stench has substance.\n");
    add_cmd_item("air", "smell", "The air is so heavy with mold "+
        "spores and decay that you gag from breathing it.\n");
    add_item(({"water", "filthy water", "wall", "walls", 
        "ceiling", "mold", "slime"}),
        "The granite walls and floor are covered in streamlets "+
        "of filthy water, mold, slime, and ick.\n");
    add_item(({"floor", "ick", "muck", "stone floor"}), 
        "The stone of the floor is slippery with ick. Be careful "+
		"you don't fall!\n");
}


void
create_room()
{
	
	add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, teleport_test);
	
//	set_terrain(({ TERRAIN_HASDEAD, TERRAIN_UNDERGROUND }));
//  producing runtime error.

    add_tomb_items();
}
