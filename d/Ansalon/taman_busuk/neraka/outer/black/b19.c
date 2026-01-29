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
	set_short("In the middle of the Black Army camp");
    set_extra_long("You are in the Black Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them.");
    set_quarter(BLACK);

    add_item_camp();
    
    add_exit(NOUTER+"black/b18","west");
    add_exit(NOUTER+"black/b23","east");
    add_exit(NOUTER+"black/b21","south");

    reset_room();
}

