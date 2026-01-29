#include "/d/Ansalon/trial/local.h"
#include <stdproperties.h>
inherit TRIAL_IN;

void
create_trial_room()
{
    set_short("On a dusty forest trail");
    set_long("@@long_descr"); 

    enable_reset(120);

	string nextRoom = TROOM + "forest67";
	add_exit(nextRoom,"north",0);
	nextRoom->add_exit(this_object(), "south", 0);

	
    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");
}

string
long_descr()
{ 
    return
    "You are standing on a small trail within a vast "+
    "emerald-green forest. The undergrowth here "+
    "consists of a wide variety of plant and herb "+
    "species. The trail continues to the north and "+
    "southwest.\n";
}
