inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Alley in the village of Leah");
	set_long("   You have entered a narrow, damp alley just west of "+
		"the centre of town. The ground is littered with dirty "+
		"rags, tin cans and old newspapers. Looming up on both "+
		"sides of the alley are the solid brick walls of two "+
		"houses. Over the walls of the buildings you can see "+
		"the tall, green trees in the surrounding forest. At "+
		"the north end of the alley there is a small townhouse.\n\n");
   
	add_item(({"house", "townhouse"}), "The house is small, kept "+
		"fairly tidy and is painted yellow.\n");
	add_item("alley", "The alley looks like the home of homeless "+
		"elves in the area.\n");
	add_item("centre", "Looking back east you can see the centre "+
		"of Leah.\n");
	add_item("rags", "There are piles of dirty rags all over the "+
		"alley. They look like they were clothes at one time in "+
		"the past.\n");
	add_item("newspapers", "The old, yellowed newspapers are folded "+
		"neatly. They make you think they may have been used as "+
		"blankets by the people who sleep here.\n");
	add_item("cans", "Tin cans litter the alley. They are burned "+
		"black. Perhaps they were used to cook food.\n");
	add_item((("bricks", "brick walls")), "The brick walls tower "+
		"tall and uninviting. It is can see no way to climb them.\n");
	add_item(({"ground"}), "The ground is littered with all manner of "+
		"debris.\n");
	add_item(({"forest", "trees"}), "The forest is dark and dense.\n");

	add_exit(VILLAGE_DIR + "centre", "east");
	add_exit(VILLAGE_DIR + "cabin1", "north");

}
