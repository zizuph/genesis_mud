#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object door;
object gloves;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_short("dark storeroom");
    set_long("@@long_descr");

    add_item(({"walls","shelves"}),
      BSN("Along the walls of this small room are shelves, that are either empty " +
	"or hold items that really don't interest you."));

    door = clone_object("/d/Ansalon/kalaman/obj/door1b");
    door->move(TO);

    gloves = clone_object(KOBJ + "armour/magic_gloves");
    gloves->move(TO);
    reset_kalaman_room();
}

string
long_descr()
{
    string str;

    str = "You stand in a dark room, used to store items of value. A few shelves line " +
    "the walls.";

    return BSN(str);
}


