inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 1
#define REVERSE 1
#define HINTINDEX 4
#define HINT2INDEX 3
#define FROM  "s"
#define FROM2 "n"

/* Room-names for the 4 neighbour rooms */
#define	NORTH	COLDIR + "white"
#define WEST	COLDIR + "col_53"
#define EAST	COLDIR + "col_55"
#define SOUTH	COLDIR + "orange"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from west " +
	"to east. On the north wall you see a white window. " +
	"on the south wall you see an orange window. In front of " +
	"those windows you see tripods." + ADD));

    hint = "0";
    hint2 = "0";
    add_exit(WEST, "west", 0);
    add_exit(EAST, "east", 0);
    set_hint();    /* update hint */
}
