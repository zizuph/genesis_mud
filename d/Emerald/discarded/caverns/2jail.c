/*
 * 2jail.c
 * This is the first room in the jail in the pirate's caverns.
 *   - Alaron September 15, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
    object door1, door2;
    
    set_short("Prison Hallway");
    set_long("   You have found yourself in what looks to be a main hallway "+
	     "through an underground prison. The cavern walls conveniently "+
	     "pull back in such a way that they form little alcoves which "+
	     "have had thick doors and bars placed in front of them to "+
	     "create crude, but effective prison cells. There is a prison "+
	     "cell to the north and there is an enormous iron door "+
	     "imbedded in the southwest wall.\n\n");
    
    add_item( ({"prison", "underground prison"}),
	     "The underground prison is formed by this natural cavern which "+
	     "has been carved and modified to create a prison.\n");

    add_item(({"cell","prison cell"}),
	     "The prison cell has been formed from a natural alcove formed "+
	     "off of the main cavern. Thick iron bars and an enormous "+
	     "barred door have been hammered and carved right into the "+
	     "black rock to keep the prisoners contained.\n");


    add_exit(THIS_DIR + "1jail", "north");
    add_exit(THIS_DIR + "1guardrm", "southwest");
    add_exit(THIS_DIR + "3jail", "east");
    
    
    seteuid(geteuid());
    door1 = clone_object(THIS_DIR+"obj/pdoor6a");
    door2 = clone_object(THIS_DIR+"obj/pdoor5b");
    door1 ->move(TO);
    door2 ->move(TO);
}

