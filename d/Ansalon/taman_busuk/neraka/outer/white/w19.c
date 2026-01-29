#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
	if (!objectp(d1))
    	d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"white");
}

void
create_neraka_room()
{
	set_short("in the White Army camp");
    set_extra_long("You are in the White Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them.");
    set_quarter(WHITE);

    add_item_camp();
    
    add_exit(NOUTER+"white/w18","east");
    add_exit(NOUTER+"white/w27","southwest");
    add_exit(NOUTER+"white/w20","west");

    reset_room();
}


