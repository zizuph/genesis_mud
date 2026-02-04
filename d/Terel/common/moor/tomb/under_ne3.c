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
        "You wonder how much longer you can stand it down here.  " +
	"The stench of decay nearly overpowers you.  The walls are beginning " +
	"to crumble here into a muck of wet sand, mortar and slimy grey " +
	"clay seeping from the cracks in the bricks that remain. Something "+
	"deep within you is screaming for you to leave this place.\n"
    );

	
    add_exit("under_tomb02", "northwest", test_exit);
    add_exit("under_ne2", "south", test_exit);
    reset_room();
}
