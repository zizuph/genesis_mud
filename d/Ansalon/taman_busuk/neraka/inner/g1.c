/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_IN;

void
create_neraka_room()
{
	set_short("in a short tunnel under the city wall");
	set_long("You are in a short tunnel under the city wall. A pair " +
	    "of torches illuminate the tunnel, casting a soft yellow " +
	    "light on the bare stone walls.\n");

    add_item_inside();
    add_item(({"torch","torches"}),"The torches are attached to the " +
        "wall.\n");

	add_prop(ROOM_I_ALLOW_STEED,1);

    add_exit(NINNER + "r1", "north");
    add_exit(NINNER + "r32", "south");

}

