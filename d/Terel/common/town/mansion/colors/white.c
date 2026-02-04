inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 4
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH	COLDIR + "col_34"
#define WEST	COLDIR + "col_43"
#define EAST	COLDIR + "col_45"
#define SOUTH	COLDIR + "col_54"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    set_short("white room");


    set_long(break_string("This room seems to be flushed in an " +
	"white light; it looks as if it just snowed here. " +
	"You never saw a cleaner white than this - it's even " +
	"dazzling you. " +
	"There are windows on all four walls which are in " +
	"white. Behind those windows there seems to be a sort of " +
	"fire which is the source of the white light in this room.\n",70));
    add_item("window","The white color of the windows makes this " +
	"room seem to be white.\n");
    add_item("windows","The white color of the windows makes this " +
	"room seem to be white.\n");
    add_item("fire","There seems to be a fire behind the glass.\n");
    add_item("glass","The glass of the windows is in white.\n");

    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
}
