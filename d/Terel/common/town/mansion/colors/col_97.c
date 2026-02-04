inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define BSN(s) break_string((s) + "\n", 70)
create_room()
{
#include "col_cross.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from west " +
		 "to east." + ADD));
    add_exit(COLDIR + "col_87", "north", 0);
    add_exit(COLDIR + "col_96", "west", 0);
    add_exit(COLDIR + "col_98", "east", 0);
  }

