inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 0
#define REVERSE 1
#define HINTINDEX 5
#define HINT2INDEX 0
#define FROM  "w"
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH   COLDIR + "col_13"
#define WEST	DUSTDIR + "hint_room0"
#define EAST	COLDIR + "violet"
#define SOUTH	COLDIR + "col_33"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from north " +
	"to south. On the east wall you see a violet window. " +
	"In front of " +
	"this window you see a tripod." + ADD));

    hint = "0";
    add_exit(NORTH, "north", 0);
    add_exit(SOUTH, "south", 0);
    add_exit(WEST, "west", 0);
    set_hint();    /* update hint */
}

