/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include <stdproperties.h>

inherit OUTER_IN;

void
create_neraka_room()
{
	set_short("in a short tunnel under the city wall");
	set_long("You are in a short tunnel under the city wall. To the " +
	    "south, the tunnel opens up onto a street. A pair of " +
	    "torches illuminate the room, casting a soft yellow light " +
	    "on the bare stone walls.\n");

    add_item_inside();
    add_item(({"torch","torches"}),"The torches are attached to the " +
        "wall.\n");
    add_item("street","The street is to the south of here, inside " +
        "the city.\n");

	add_prop(ROOM_I_ALLOW_STEED,1);

    add_exit(NINNER + "r1", "south");

    clone_object(NOUTER + "main/in_gate")->move(TO);
}

