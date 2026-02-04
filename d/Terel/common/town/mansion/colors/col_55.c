inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define BSN(s) break_string((s) + "\n", 70)
create_room()
{
#include "col_cross.h"
    set_short("crossing of hallways");
    set_long(BSN("This is a crossing of two hallways, " +
		 "one from north to south, the other from " +
		 "west to east." + ADD));
    add_exit(COLDIR + "col_45", "north", 0);
    add_exit(COLDIR + "col_65", "south", 0);
    add_exit(COLDIR + "col_54", "west", 0);
    add_exit(COLDIR + "col_56", "east", 0);
  }

