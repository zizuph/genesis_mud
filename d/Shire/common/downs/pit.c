inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_room() {
    set_short("beneath the Barrow Downs");
    set_long(break_string(
	  "You are inside some kind of a tunnel system, "
	+ "beneath the surface of the Barrow Downs. "
	+ "Here, lost souls of long forgotten years rule. "
	+ "Beware of the darkness, for now it hides you, "
	+ "but it may betray you just as well... "
	+ "There is a hole in the ground.\n",70));

    add_item(({"hole","ground"}),("There used to be an exit here, but it caved in upon your entrance.\n"));
 	
    add_exit(DOWNS_DIR + "stone2_1", "north");
    

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}
