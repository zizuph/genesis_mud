#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 21 May 97 */

inherit OUTER_OUT;

object sarge,soldier1,soldier2,soldier3;

void
reset_neraka_room()
{
	if (!objectp(soldier3))
    	soldier3 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
	if (!objectp(soldier2))
    	soldier2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
	if (!objectp(soldier1))
    	soldier1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"black");
    if (!objectp(sarge))
    {
    	sarge = clone_npc(NNPC + "humsergeant","black");
        sarge->start_patrol();
        sarge->set_patrol_time(30);
        sarge->set_patrol_path(({"sw","se","s","s","s","n","n","ne","ne",
            "nw","w"}));
    }
}

void
create_neraka_room()
{
	set_short("Dirt road in Black Quarter");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "The road leads southwest and east. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    
    add_exit(NOUTER+"black/b13","east");
    add_exit(NOUTER+"black/b5","southwest");

    reset_room();
}

