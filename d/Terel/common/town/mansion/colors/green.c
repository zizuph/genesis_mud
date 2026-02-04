inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 2
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH	COLDIR + "col_56"
#define WEST	COLDIR + "col_65"
#define EAST	COLDIR + "col_67"
#define SOUTH	COLDIR + "col_76"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    set_short("green room");
    set_long(break_string("This room appears all in green. The strange " +
	"color is caused by four windows of green glass on all walls. " +
	"From behind the windows, the light of a fire shines through. " +
	"The light is coloured green by the windows.\n",70));
    add_item("window","The windows have green glasses.\n");
    add_item("windows","The windows have green glasses.\n");
    add_item("glass","The glass is in green.\n");
    add_item("glasses","The glass is in green.\n");
    add_item("light","The light is colored green by the windows.\n");
    add_item("fire","You can't see the fire from here.\n");
    add_item("fires","You can't see the fire from here.\n");
    clone_object(TOWNDIR + "mansion/obj/balance")->move(this_object());
    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
}
