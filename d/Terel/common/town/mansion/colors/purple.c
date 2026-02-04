inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTINDEX 1
#define TWOHINTS 0
#define REVERSE 0
#define HINT2INDEX 0
#define FROM 0
#define FROM2 0

/* Room-names for the 4 neighbour rooms */
#define NORTH	COLDIR + "col_76"
#define WEST	COLDIR + "col_85"
#define EAST	COLDIR + "col_87"
#define SOUTH	COLDIR + "col_96"

#include "/d/Terel/common/town/mansion/colors/colorpath.h"

create_room()
{
    set_short("purple room");
    set_long(break_string("This room appears all in purple. The strange " +
	"color is caused by 4 windows of purple glass on all walls. " +
	"from behind the windows, the light of a fire shines through. " +
	"The light is coloured purple by the windows.\n",70));
    add_item("window","The windows have purple glasses.\n");
    add_item("windows","The windows have purple glasses.\n");
    add_item("glass","The glass is in purple.\n");
    add_item("glasses","The glass is in purple.\n");
    add_item("light","The light is colored purple by the windows.\n");
    add_item("fire","You can't see the fire from here.\n");
    add_item("fires","You can't see the fire from here.\n");
    hint = "n";
    do_add_exit(); /* Add dummy exit */
    set_hint();    /* update hint */
}
