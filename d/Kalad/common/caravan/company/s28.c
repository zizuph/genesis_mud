#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This long corridor is devoid of any furnishings. The walls are "+
      "just bare stone, however the floor is worth of some note, since it "+
      "is made of marble. The hallway continues to the north and south.\n");

    add_item(({ "walls" }), "The walls are made of plain white stone.\n");

    add_item(({ "floor" }), "The ground is covered with bleach-white marble "+
      "tiles that are such a brilliant white in color you are nearly "+
      "blinded for looking too long.\n");

    add_exit(CVAN + "company/s11", "north");
    add_exit(CVAN + "company/s35", "south");
}
