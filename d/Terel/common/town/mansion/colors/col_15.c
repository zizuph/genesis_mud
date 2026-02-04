inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define BSN(s) break_string((s) + "\n", 70)
create_room()
{
#include "col_cross.h"
    set_short("corner");
    set_long(BSN("This is a corner. One hallway runs south from here, " +
     "another runs west, and an exit stands to the north." + ADD));
    add_exit(COLDIR + "col_25", "south", 0);
    add_exit(COLDIR + "col_14", "west", 0);
   add_exit(MANSION + "second/hall1", "north", 0);
}

