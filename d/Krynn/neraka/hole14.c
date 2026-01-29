/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are down a hole" +
	"", SL));

    add_exit(TDIR + "city14", "up", 0);

    DARK;

    door = clone_object(OBJ + "d_city14_b");
    door->move(TO);
}
