inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 0
#define REVERSE 1
#define HINTINDEX 0
#define HINT2INDEX 0
#define FROM  "s"
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH   COLDIR + "blue"
#define WEST	COLDIR + "col_97"
#define EAST	COLDIR + "col_99"
#define SOUTH	"dummy"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from west " +
	"to east. On the north wall you see a blue window. " +
	"In front of " +
	"this windows you see a tripod." + ADD));

    hint = "0";
    add_exit(WEST, "west", 0);
    add_exit(EAST, "east", 0);
    set_hint();    /* update hint */
}

