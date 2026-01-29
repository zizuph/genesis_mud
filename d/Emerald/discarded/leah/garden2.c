inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Outside tower");
	set_long("   You are lazily wandering around the beautiful "+
		 "gardens outside a large white marble tower. The gardens "+
		 "are well-kept and fabulously rich in flowers. The smell "+
                 "of roses and lilacs soften the hearts of the wildest "+
                 "of animals.\n\n");

	add_exit(VILLAGE_DIR + "garden4", "southeast",);
	add_exit(VILLAGE_DIR + "garden3", "southwest",);

	add_item(({"tower"}), "The tower is extremely impressive, built from "+
		   "pure white marble and beautifully made.\n");
	add_item(({"gardens","garden"}),"The gardens are well-kept and must "+
		   "cost a fortune to upkeep by the owner of the tower.\n");
        add_item(({"flowers"}), "The flowers are a riot of colour, spreading "+
	         "everywhere in the garden. The gardener must have put some "+
	         "real effort into his work to get this effect.\n");

	add_prop(ROOM_I_INSIDE, 0);
}

