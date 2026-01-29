#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include ARND_MEET

/* Carridin */

inherit OUTER_OUT;

object sarge, soldier1, soldier2, soldier3;

void
reset_neraka_room()
{
	if (!soldier3)
    	soldier3 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"red");
	if (!soldier2)
    	soldier2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"red");
	if (!soldier1)
    	soldier1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"red");
    if (!sarge)
    {
    	sarge = clone_npc(NNPC + "humsergeant","red");
        sarge->start_patrol();
        sarge->set_patrol_time(30);
        sarge->set_patrol_path(({"n","w","w","nw","s","s","s","s","se",
            "ne","n","se","ne","w","n"}));
    }
}

void
create_neraka_room()
{
	set_short("The market square in the Red Quarter");
    set_extra_long("You are at the northern end of the market square. " +
		"Apart from the merchants who wander the marketplace, various shops " +
		"and establishments line the square. Going further southwards would " +
		"give you a better view of the area.");
	set_quarter(RED);
	add_item_market("square");
	add_item_sidewalks();
	add_item_buildings();

    add_exit(NOUTER+"red/r6","north",0,0,0);
    add_exit(NOUTER+"red/r13","southeast",0,0,0);
    add_exit(NOUTER+"red/r12","south",0,0,0);
    add_exit(NOUTER+"red/r11","southwest",0,0,0);

	reset_room();
}
