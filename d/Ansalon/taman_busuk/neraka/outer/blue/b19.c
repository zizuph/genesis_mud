#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar */

inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"blue");
}

void
create_neraka_room()
{
	set_short("Dirt road in Blue Army camp");
    set_extra_long("You are walking on a dirt road in the Blue Army camp. " +
        "There is a tent to the south, and the road leads northwest " +
        "from here.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_camp();
    remove_item("tent");
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap"}),"The flap covers the " +
        "entrance to the tent, to keep the heat in on cold nights.\n");

    add_exit(NOUTER+"blue/b18","northwest");
    add_exit(NOUTER+"blue/t4","south","@@msg");
    reset_room();
}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

