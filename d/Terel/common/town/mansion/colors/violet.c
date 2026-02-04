inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 5
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH	COLDIR + "col_14"
#define WEST	COLDIR + "col_23"
#define EAST	COLDIR + "col_25"
#define SOUTH	COLDIR + "col_34"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    object box;
    set_short("violet room");

    set_long(break_string(
	"This room is completely in violet: the carpet is violet, and heavy, " +
	"violet curtains fall down from the ceiling. The ceiling " +
	"itself is emitting a violet light. " +
	"There are windows on all four walls which are in " +
	"violet as well. Behind those windows there seems to be a sort of " +
	"fire which could be source of the violet light in this room.\n",70));
    add_item("window","The violet color of the windows makes this " +
	"room seem to be violet.\n");
    add_item("windows","The violet color of the windows makes this " +
	"room seem to be violet.\n");
    add_item("fire","There seems to be a fire behind the glass.\n");
    add_item("glass","The glass of the windows is in violet.\n");
    box = clone_object(TOWNDIR + "mansion/obj/box0");
    box->move(this_object());
    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
}
