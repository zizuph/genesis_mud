inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define BSN(s) break_string((s) + "\n", 70)
create_room()
{
#include "col_cross.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from north " +
		 "to south." + ADD));
    add_exit(COLDIR + "col_23", "north", 0);
    add_exit(COLDIR + "col_43", "south", 0);
    add_exit(COLDIR + "col_34", "east", 0);
}

