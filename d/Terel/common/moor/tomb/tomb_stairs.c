// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
/* from the imagination of Lord Sorgum ;)  */

#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"

int
check_prop()
{
    if (TP->query_prop(COFFIN_ROUTE))
    {
        write("Having navigated these slippery stairs before, you "+
            "know just where to step and you make your way up "+
			"the slimy stairs with few mishaps.\n");
        return 0;
	}
	else
    write("The stairs are too slippery for you to keep your "+
        "footing long enough to make it the rest of the way "+
        "up the steep, winding staircase.\n");	
    return 1;		

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
create_room()
{
		::create_room();
		
    add_npc(MOBDIR +"dweller4", 1);
    set_short("Tomb stairs");
    set_long("This is a tall staircase of rough-hewn stone. "+
        "It is narrow and spirals downward into the bowels of the "+
		"hill beneath the tomb. The walls are made of stone blocks "+
        "and crumbling mortar. Slime seems to coat every step. "+
        "The pungent odor of decay is quite unbearable.\n"
    );

    add_prop(ROOM_I_LIGHT, -1);

    add_exit("tomb03", "up", check_prop);
    add_exit("under_tomb02", "down", test_exit);    
}
