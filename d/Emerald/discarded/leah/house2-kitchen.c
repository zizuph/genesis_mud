inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{

    set_short("A small kitchen.");
    set_long(" This is a rather small kitchen with a wood-burning "+
	"oven, a cupboard, a counter, and .\n\n");

    add_item(({"village", "Leah"}), "The village spreads out before you "+
      "inviting you to explore it further.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(LEAH_DIR + "house2-main", "north");
}
