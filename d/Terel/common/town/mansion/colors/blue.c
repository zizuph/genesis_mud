inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define OBJDIR TOWNDIR + "mansion/obj/"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 0
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define	NORTH	COLDIR + "col_78"
#define	WEST	COLDIR + "col_87"
#define	EAST	COLDIR + "col_89"
#define	SOUTH	COLDIR + "col_98"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    set_short("blue room");
    set_long(break_string("This room look as if it would be under " +
	"water. There are windows on all four walls which are in " +
	"blue. Behind those windows there seems to be a sort of " +
	"fire which is the source of the blue light in this room.\n",70));
    add_item("window","The blue color of the windows makes this " +
	"room seem to be blue.\n");
    add_item("windows","The blue color of the windows makes this " +
	"room seem to be blue.\n");
    add_item("fire","There seems to be a fire behind the glass.\n");
    add_item("glass","The glass of the windows is in blue.\n");
    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
    clone_object(OBJDIR + "mirror")->move(this_object());
}
