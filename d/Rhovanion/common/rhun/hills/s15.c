
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Seaside");
    set_long("The sandy beach continues here from north to south.  "+
	"Out on the sea, you can see a few fishing boats and other "+
	"craft.\n");
	
    AE(RHUN+"hills/s16", "south");
    AE(RHUN+"hills/s9", "north");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the north and south.\n");
    add_item(({"sea", "boats", "boat", "craft"}), "A few small "+
	"boats, most likely fishermen, are out on the Sea of Rhun "+
	"trying to scrape out their living.\n");
}
