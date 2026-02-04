// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
/* from the imagination of Lord Sorgum ;)  */

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
	
    add_npc(MOBDIR +"dweller1", (1 +random(3)));
	add_npc(MOBDIR +"hound", 1);
	
    set_short("Under the tomb");
    set_long("Underneath the entrance to the ancient tomb the "+
        "air is cold and damp "+
        "and filled with a sickening musty stench. Filthy water "+
        "drips from the walls and ceiling. The floor is slippery "+
        "with ick. Two tunnels branch away from here, slanting "+
        "steeply downwards, into the stygian depths.\n");

    add_prop(ROOM_I_LIGHT, -1);
	
    add_exit("tomb01", "up", 0);
    add_exit("under_nw", "northwest", test_exit);
    add_exit("under_ne", "northeast", test_exit);    

}


