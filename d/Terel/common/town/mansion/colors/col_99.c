inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define BSN(s) break_string((s) + "\n", 70)
create_room()
{
#include "col_cross.h"
    set_short("corner");
    set_long(BSN("This is a corner. One hallway runs north from here, " +
		 "another hallway runs west from here." + ADD));
    add_exit(COLDIR + "col_89", "north", 0);
    add_exit(COLDIR + "col_98", "west", 0);
}

