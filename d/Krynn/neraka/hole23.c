
/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

create_tantallon_room()
{
    object door;

    set_short("Down a hole");
    set_long(BS(
    	"You are in a small hole. It looks like this place once was used as " +
	"a small cell but now it's empty." +
    " You can still see some straw here which must have been " +
    "the prisoner's bed.", SL));

    add_item(({"straw","bed"}),
             BS("Looking closely at the straw, you notice a hidden exit " +
                "further down.",SL));

    add_exit(TDIR + "city23", "up", 0);
    add_exit("/d/Krynn/solamn/palanthas/shipping/pipe4","down",0/*"@@block@@"*/,0,1);

    door = clone_object(OBJ + "d_city23_b");
    door->move(TO);
}

int
block()
{
    write("It does not seem possible to go this way currently.\n");
    return 1;
}
