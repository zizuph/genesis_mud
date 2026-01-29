/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are down in a hole or, or rather a cave. It's wet and cold and " +
    	"the walls are covered with some green slime. This looks like a very " +
	"unfriendly place. There is something that looks like a cell south." +
	"", SL));

    add_item("walls", "The walls are cold, wet and covered with slime, Yuk.\n");

    add_exit(TDIR + "city13", "up", 0);
    add_exit(TDIR + "sal_cell", "south", 0);

    DARK;

    door = clone_object(OBJ + "d_city13_b");
    door->move(TO);
}
