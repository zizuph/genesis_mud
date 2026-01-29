#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Stairs");
    set_long("This room is empty save for the large set of stairs that "+
      "spirals downward. A small hallway to the east leads into another "+
      "passageway.\n");

    add_item(({ "stairs" }), "A metal frame staircase that leads to the "+
      "first floor of the building.\n");

    add_exit(CVAN + "company/s34", "down");
    add_exit(CVAN + "company/s65", "east");
}
