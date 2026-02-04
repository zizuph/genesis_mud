// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room. 
 
#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"


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
create_room()
{    
	::create_room();
	
    add_npc(MOBDIR +"dweller3", 2);
	
    set_short("Under the tomb");
    set_long(
        "This deep underneath the tomb the air is cold and damp and filled with " +
        "a sickening musty stench. Filthy water drips from the walls and " +
        "ceiling. The feeling of decay and deterioration is so intense "+
		"that it seems very unsafe to be here.\n"
    );

    add_prop(ROOM_I_LIGHT, -1);
	
    add_exit("tomb_core", "north", test_exit);
    add_exit("under_ne3", "southeast", test_exit);
    add_exit("under_nw3", "southwest", test_exit);
	add_exit("tomb_stairs", "up", 0);     // to coffin room

    reset_room();
}
