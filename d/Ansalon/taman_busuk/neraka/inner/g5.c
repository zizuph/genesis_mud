/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_IN;

object g1,g2;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(NNPC + "cityguard");
    if (!objectp(g2))
        g2 = clone_npc(NNPC + "cityguard");
}

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

    add_exit(NINNER + "r23", "east");
    add_exit(NINNER + "r45", "west");

    reset_room();
}

