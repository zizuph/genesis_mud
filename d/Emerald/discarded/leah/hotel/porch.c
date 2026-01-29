inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Porch");
    	set_long("   This is a quiet peaceful place. The porch "+
		 "is surrounded by a tall cedar fence. There is "+
		 "a cedar swing built for two on the porch. There "+
		 "are a few potted plants.  And a small tree in a "+
		 "large pot. The plants all sit in the corners.\n\n");

	add_item("fence", "The cedar fence is tall and allows no "+
		"one to see in or out of the suite.\n");
	add_item("swing", "The swing is built for two.  Perhaps you "+
		"will want to sit and swing in it.\n");
	add_item("tree", "The tree is small.  It has small delicate "+
		"leaves that bow down.\n");
	add_item("plants", "The plants are flowers.  They look like "+
		"violets, and dusty roses.  They are very delicate "+
		"and pretty. You would not dare to pick them.\n");
	add_item("pot", "The pots contain several different kinds "+
		"of plants.\n");
 
	add_exit(VILLAGE_DIR + "hotel/bed1", "east");
}
