inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Lover's suite");
	set_long("   Upon entering the lover's suite you notice a well "+
		 "lit fire in the fireplace.  A large bed with pillows. "+
		 "There is a rug centered in front of the fireplace. "+
		 "There is a painting hug over the bed with a plaque "+
		 "under it.\n\n");

	add_item("fireplace", "The fireplace was just lit and should "+
		 "last hours. So you should not have to tend to it.\n");
	add_item("bed", "It is a large bed.  There are two big fluffy "+
		 "pillows on it.\n");
	add_item("rug", "The rug is centered in front of the fireplace. "+
		 "It is round soft and has a mixture of colours in it.\n");
	add_item("painting", "The painting shows two lovers holding each "+
		 "other in the heat of passion.\n");
	add_item("plaque", "The plaque is gold and reads The Lovers.  There "+
		 "is no author.\n");

	add_prop(ROOM_I_INSIDE, 1);

	add_exit(VILLAGE_DIR + "hotel/hall" , "east"); 
	
}
