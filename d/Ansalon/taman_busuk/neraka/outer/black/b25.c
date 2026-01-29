#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET
/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

object d1, d2;

void
reset_neraka_room()
{
	if (!objectp(d1))
    	d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"black");
    if (!objectp(d2))
    	d2 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"black");
}

void
create_neraka_room()
{
	set_short("In the Black Army camp");
    set_extra_long("You are in the Black Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them. There are two entrances to tents to the east and " +
        "south. ");
    set_quarter(BLACK);

    add_item_camp();

    remove_item("tent");
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap","entrance","entrances"}),
        "A flap covers the entrance to the tent, to keep the heat in " +
        "on cold nights.\n");

    add_exit(NOUTER+"black/b24","north");
    add_exit(NOUTER+"black/t7","east","@@msg");
    add_exit(NOUTER+"black/t2","south","@@msg");
    add_exit(NOUTER+"black/b21","northwest");

    reset_room();
}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

