#include "defs.h"

inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h"

create_rom()
{
    set_short("North of crossing in Bree");
    set_long(
	    "You are standing north of the intersection in Bree. South-east you can see "+
	    "'The Prancing Pony', a large and well kept Inn with the entrance south "+
	    "of here. North of here is an intersection. There are two buildings on "+
	    "each side of the intersection.  A new building lies west and a busy "+
	    "hobbit-hole is east.\n");

   add_exit(BREE_DIR + "crossing","south",0,2);
     add_exit(BREE_DIR + "ncross","north",0,3);
     add_exit(BREE_DIR + "post","east",0,1);
    add_exit(BREE_DIR + "advguild","west",0,1);

    add_item(({"crossing","eastroad"}),
	    "The road is well used since it is a major walk for "+
	    "adventurers and local inhabitants. \n");

    add_item(({"buildings","houses","building","house"}),
	    "The building on your lefthand side north of here is rather large "+
	    "and you can see smoke coming out of the building, as if someone is "+
	    "heating something. The other building is not more then half the size "+
	    "of the first building , but it looks new and of great wealth.\n");
    
    add_item(({"new building","hobbit hole","hole","hobbit-hole"}), "The "+
            "building to the west is a place for adventurers, and "+
            "the hobbit-hole east is full of hobbits carrying mail.\n");
}
