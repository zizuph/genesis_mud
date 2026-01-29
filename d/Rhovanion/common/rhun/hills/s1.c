
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Under the pier");
    set_long("The mouth of the River Carnen is here, emptying "+
	"from its long journey into the Sea of Rhun.  You may "+
	"follow along the riverbank to the northwest, or take "+
	"the sandy beach southward.\n");
	
    AE(RHUN+"hills/r1", "northwest");
    AE(RHUN+"hills/s2", "south");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the south.\n");
    add_item("river", "The river empties here into the Sea of "+
	"Rhun.\n");
}

