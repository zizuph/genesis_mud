inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

#define TWOHINTS 1
#define REVERSE 1
#define HINTINDEX 0
#define HINT2INDEX 1
#define FROM  "w"
#define FROM2 "e"

/* Room-names for the 4 neighbour rooms */
#define	NORTH	COLDIR + "col_77"
#define WEST	COLDIR + "purple"
#define EAST	COLDIR + "blue"
#define SOUTH	COLDIR + "col_97"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

#define BSN(s) break_string((s) + "\n",70)

create_room()
{
#include "col_hall.h"
    set_short("hallway");
    set_long(BSN("This is a hallway running from north " +
	"to south. On the west wall you see a purple window. " +
	"on the east wall you see a blue window. In front of " +
	"those windows you see tripods." + ADD));

    hint = "0";
    hint2 = "0";
    add_exit(NORTH, "north", 0);
    add_exit(SOUTH, "south", 0);
    set_hint();    /* update hint */
}
