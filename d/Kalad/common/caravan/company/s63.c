#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

object ob1;

void reset_room();

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
      "third floor of the building.\n");

    add_exit(CVAN + "company/s62", "west");
    add_exit(CVAN + "company/s76", "up");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcguard");
	ob1->move_living("M",TO);
    }
}
