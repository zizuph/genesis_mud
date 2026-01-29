#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;


object sarge, soldier1, soldier2, soldier3;

void
reset_neraka_room()
{
	if (!objectp(soldier3))
    	soldier3 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
	if (!soldier2)
	    soldier2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
	if (!soldier1)
        soldier1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
    if (!sarge)
    {
    	sarge = clone_npc(NNPC + "humsergeant","black");
        sarge->start_patrol();
        sarge->set_patrol_time(30);
        sarge->set_patrol_path(({"s","e","se","n","n","n","w","sw"}));
    }
}

void
create_neraka_room()
{
	set_short("End of a small dirt road in the Black Quarter");
    set_extra_long("You are at the end of a small dirt road in the " +
        "Black Quarter. The road leads west from here, while to the " +
        "east the army camp is spread out. " +
        "There are wooden sidewalks along the " +
        "roads here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item(({"camp","army camp"}),
        "The army camp is spread out east of here.\n");

    add_exit(NOUTER+"black/b15","west");
    add_exit(NOUTER+"black/b20","northeast");
    add_exit(NOUTER+"black/b19","east");
    add_exit(NOUTER+"black/b21","southeast");

    reset_room();
}

