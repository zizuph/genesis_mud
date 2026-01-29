#include "defs.h"

object loaf;

CONSTRUCT_ROOM {
    set_short("The secret gathering room.");
    set_long("The secret gathering room. This is a small room behind some "+
	     "rocks, obviously made by dwarves, examining all the food left "+
	     "over here. It is clear that the dwarves are afraid of being "+
	     "discovered by the trolls, but what can you do to help them? "+
	     "You can go south behind the blocks.\n");
    EXIT("dirtrock","south");
    add_item(({"blocks","exit","rocks"}),
	     "You see nothing special.");
    add_item("food",
	     "Well, it is only leftovers. Nothing much to eat I am afraid.");
    RESET_ROOM;
}

RESET_ROOM {
    if (!loaf || !present(loaf)) {
	loaf = clone_object(MORIA_OBJ+"loaf");
	loaf -> move(TO);
    }
}

/*
      loaf->set_eater_mess("Umm! Wonderful taste of this dwarvish "+
			   "foodstuff!\n");
      loaf->set_eating_mess(" grabs a piece of loaf and hurls it down "+
			    "his throut.\n");
*/
