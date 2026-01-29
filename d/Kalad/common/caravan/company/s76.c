#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Stairs");
    set_long("You have reached a section of the hallway which is "+
      "dominated by a large set of stairs that spirals downward. The only "+
      "other thing of note is the marble floor of this passageway. The "+
      "hallway continues to the north and south.\n");

    add_item(({ "stairs" }), "A metal frame staircase that leads to the "+
      "second floor of the building.\n");

    add_item(({ "floor" }), "The ground is covered in marble tiles of such a "+
      "brilliant white color, that you are nearly blinded from gazing at "+
      "them.\n");

    add_exit(CVAN + "company/s75", "north");
    add_exit(CVAN + "company/s63", "down");
    add_exit(CVAN + "company/s77", "south");
}
