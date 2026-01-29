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
        "around them. A metal grating covers a pit in the ground. To " +
        "the east is a large stone hut.");
    set_quarter(BLACK);

    add_item_camp();
    
    add_item(({"grating","metal grating"}),"The metal grating covers " +
        "a pit in the ground, leading down into murky darkness.\n");
    add_item(({"pit","hole"}),"The pit leads down into murky darkness. " +
        "A foul smell comes from the hole.\n");
    add_item(({"hut","stone hut","large hut","large stone hut"}),
        "The hut is made of stone, with a roof of thatch.\n");

    add_exit(NOUTER+"black/b22","north");
    add_exit(NOUTER+"black/b19","west");
    add_exit(NOUTER+"black/b24","south");
    add_exit(NOUTER+"black/hut","east");
    add_exit(NOUTER+"pens/p20","down","@@grating",1,1);

    reset_room();
}

int
grating()
{
	write("You pull the grating aside and jump down into the pit.\n");
    return 0;
}

