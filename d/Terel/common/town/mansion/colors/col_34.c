inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 1
#define REVERSE 1
#define HINTINDEX 5
#define HINT2INDEX 4
#define FROM  "s"
#define FROM2 "n"

/* Room-names for the 4 neighbour rooms */
#define	NORTH	COLDIR + "violet"
#define WEST	COLDIR + "col_33"
#define EAST	COLDIR + "col_35"
#define SOUTH	COLDIR + "white"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from west " +
	"to east. On the north wall you see a violet window. " +
	"on the south wall you see a white window. In front of " +
	"those windows you see tripods." + ADD));

    hint = "0";
    hint2 = "0";
    add_exit(WEST, "west", 0);
    add_exit(EAST, "east", 0);
    set_hint();    /* update hint */
}
