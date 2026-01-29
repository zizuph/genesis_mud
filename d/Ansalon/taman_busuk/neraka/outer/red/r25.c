#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include ARND_MEET

/* Carridin */
/* add human/half-elf guards */

inherit OUTER_OUT;

object d1 = 0,d2 = 0;

void
reset_neraka_room()
{
	if (!d1)
    	d1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"red");
	if (!d2)
    	d2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"red");
}
void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("You are travelling along a well-used road in the Red Quarter. " +
		"Just south of here lies the Red Army camp. " +
		"Wooden sidewalks line the roads here, since wagons and horses usually " +
		"travel on the dirt roads.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_camp();

    add_exit(NOUTER+"red/r18","northeast",0,0,0);
    add_exit(NOUTER+"red/r26","south",0,0,0);
	reset_room();
}



