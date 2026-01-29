/*
 * 2K2.c
 * Second Floor of Castle Telberin
 * Re-described, updated, items added, exit to balcony added.
 * by Alaron August 22, 1996
 * Updated by Alaron, August 30, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway");
    set_long("   You are at a corner in the long, lamplit hallway. The "+
	     "smooth, emerald green stone walls lead off to the east "+
	     "revealing the rest of the second floor, and south out "+
	     "onto an open-air balcony. The green color of the walls "+
	     "seems to glow and radiate against the dim, orange glow "+
	     "of the hanging wall lamps. The effect of the lighting in "+
	     "the hallway is calming and reassuring.\n"+
	     "Tapestries, paintings and trophies line the walls, adding "+
	     "a feeling of comfort and relaxation to the hallway. The faint "+
	     "odor of lamp oil and warm, sweet-smelling refreshments "+
	     "lingers in the air.\n\n");
    
    add_item(({"south", "balcony", "open-air balcony"}),
	     "The open-air balcony to the south rests above the central "+
	     "courtyard on the floor below. It presents a beautiful view "+
	     "of the fountain to its occupants. There are several chairs "+
	     "and tables on the balcony for guests to sit and enjoy the view "+
	     "over conversation or their meals.\n");
    add_item(({"chairs", "tables"}),
	     "The chairs and tables out on the balcony air of a finely "+
	     "carved wood, with thick, dark iron legs for additional "+
	     "support. They look quite comfortable, and suited for "+
	     "sitting and enjoying the view over a meal or conversation.\n");

    add_item(({"tapestries", "paintings", "trophies"}),
	     "The tapestries, paintings and trophies lining the walls all "+
	     "seem expertly hung. They are all arranged neatly and "+
	     "carefully so that no single piece has more presence than "+
	     "any of the others. The scenes on the tapestries depict "+
	     "valiant efforts of elves, rousing victories and other "+
	     "historic moments of Telberin. The paintings all depict "+
	     "various Kings, Queens and other members of royalty or "+
	     "respected elves. The trophies are much along the same lines, "+
	     "being for heroic deeds of valour, bravery and honour.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(CASTLE_DIR + "2k3","east",0);
    add_exit(CASTLE_DIR + "2k1","north",0);
    add_exit(CASTLE_DIR + "2k11","south",0);
}

