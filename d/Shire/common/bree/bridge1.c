#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("bridge");
    set_long(break_string(
	  "You are on the east side of the Brandywine Bridge, "
	+ "connecting the Shire with the Bree area. "
	+ "The bridge is old but made of solid rocks "
	+ "and it looks safe to pass. "
	+ "There is a road north, towards the mountains...\n",70));

    add_exit(BREE_DIR + "gatekeeper", "west");
    add_exit(STAND_DIR + "eroad2", "east");
    add_exit(STAND_PARENT + "guild/rooms/hguild", "north");

    clone_object(STAND_DIR + "sign")->move(this_object());
}


closed() {
   write("Sorry, the forest is closed for the moment.\n");
   return 1;
}
