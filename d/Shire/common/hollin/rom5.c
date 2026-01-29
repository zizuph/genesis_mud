#include "outroom.h"

object dragon;

create_outroom() {
   set_short("Scree");
   set_long(
	    "The steep path stops at a scree. "+
	    "There are no other possibilities except to go back south. ");
   ADD_EXA("scree",
        "The path disappears under the scree, thereby blocking you from going north.");
   ADD_EXA("path","The only exit is south.");
   SOUTH("rom4");
}

/*
   dragon = clone_object(STD_NPC+"testdragon");
   dragon -> setup_flying(this_object());
   add_exit(file_name(dragon->query_air_room()),"up");
*/
