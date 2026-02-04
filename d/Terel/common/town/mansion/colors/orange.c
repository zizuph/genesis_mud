inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 3
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH	COLDIR + "col_54"
#define WEST	COLDIR + "col_63"
#define EAST	COLDIR + "col_65"
#define SOUTH	COLDIR + "col_74"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    set_short("orange room");


    set_long(break_string("This room seems to be flushed in an " +
	"orange light, as if it would be burning. " +
	"There are windows on all four walls which are in " +
	"orange. Behind those windows there seems to be a sort of " +
	"fire which is the source of the orange light in this room.\n",70));
    add_item("window","The orange color of the windows makes this " +
	"room seem to be orange.\n");
    add_item("windows","The orange color of the windows makes this " +
	"room seem to be orange.\n");
    add_item("fire","There seems to be a fire behind the glass.\n");
    add_item("glass","The glass of the windows is in orange.\n");

    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
}
