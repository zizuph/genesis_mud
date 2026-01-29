/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are down a hole. There is a small tunnel going south. From it " +
   "you feel radiation of evil coming." +
	"", SL));

    add_exit(TDIR + "city20", "up", 0);
    add_exit(TDIR + "under10", "south", 0);

    DARK;

    door = clone_object(OBJ + "d_city20_b");
    door->move(TO);
}
