#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Stairs");
    set_long("This room is empty save for the large set of stairs that "+
      "spirals upward. A small hallway to the west heads back to the other "+
      "passageway.\n");

    add_item(({ "stairs" }), "A metal frame staircase that leads to the "+
      "second floor of the building.\n");

    add_exit(CVAN + "company/s35", "west");
    add_exit(CVAN + "company/s66", "up");
}

int
block()
{
    write("The staircase has been blocked at its summit by a large metal "+
      "door. There is no way past it.\n");
    return 1;
}
