#pragma strict_types
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");

#include <macros.h>
#include <stdproperties.h>

#include "locals.h"

void
create_room()
{
    set_short("a small cosy house");
    set_long(BSN("This is a cosy and neat blockhouse. Everything is "+ 
	"meticulously clean, but it is obvious the people "+
	"living here must be poor. The interior of the hut consists "+ 
	"of a single room where the family sleeps, eats, and "+ 
	"lives. In a corner is an open fireplace that is also used "+ 
	"to cook the meals. Along the south wall, there are several "+ 
	"straw mattresses on the floor, which serve as beds for lack "+
	"of anything better."));

    INSIDE;  /* This room is a inside room */

    add_item("fireplace","The fireplace is just big enough to serve as "+
      "a cooking place and as the main source of heat in the house.\n");
    add_item(({"mattresses","mattress","bed","beds"}), 
      "The mattresses are plain sacks filled with straw. Woolen blankets lie "+
      "upon the sacks.\n");
    add_item(({"floor",}),"On the somewhat dirty floor lays some mattresses.\n");
    add_item("painting","This is a beautiful portrait of a young "
      + "woman, she has dark hair and the most beautiful green "
      + "eyes, next to her stands a man, obviously hopelessly "
      + "in love.\n");

    add_exit(THORN_DIR + "r2d","north", "@@leave_out",1);

}

int
leave_out()
{
    write("You walk through the door and out into the light.\n");
    return 0;
}



