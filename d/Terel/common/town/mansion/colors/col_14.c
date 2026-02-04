inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 0
#define REVERSE 1
#define HINTINDEX 5
#define HINT2INDEX 0
#define FROM  "n"
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH   "dummy"
#define WEST	COLDIR + "col_13"
#define EAST	COLDIR + "col_15"
#define SOUTH	COLDIR + "violet"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from west " +
	"to east. On the south wall you see a violet window. " +
	"In front of " +
	"this windows you see a tripod." + ADD));

    hint = "0";
    add_exit(WEST, "west", 0);
    add_exit(EAST, "east", 0);
    set_hint();    /* update hint */
}

