#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include ARND_MEET

/* Carridin */

inherit OUTER_OUT;

object sarge, soldier1, soldier2, soldier3;

void
reset_neraka_room()
{
	if (!objectp(soldier3))
    	soldier3 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"green");
	if (!soldier2)
    	soldier2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"green");
	if (!soldier1)
    	soldier1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"green");
    if (!sarge)
    {
    	sarge = clone_npc(NNPC + "humsergeant","green");
        sarge->start_patrol();
        sarge->set_patrol_time(30);
        sarge->set_patrol_path(({"w","w","w","sw","s","s","e","e",
			"ne","ne","n","n","n","n","ne","se","s","s","s","w","w"}));
    }
}

void
create_neraka_room()
{
	set_short("Market square in the Green Quarter");
	set_extra_long("You are standing on the Green Quarter market " +
		"square. Apart from the merchants who wander here, various " +
		"services can be found around the square. Northwest of here " +
		"lies a post office, while to the southwest you spot a bar. " +
		"Roads lead away from the square to the north, east and " +
		"southeast while the Green Dragonarmy spreads out to the " +
		"west and south.");
	set_quarter(GREEN);

	add_item_market("square");
	add_item_sidewalks();
	add_item_camp();
	add_item_dirtroad();

	add_item("bar", "An excellent place to quench your thirst.\n");
	add_item(({"post office", "office", "post"}),
		"You can use the postal service of Neraka to write letters " +
		"and messages to far away lands.\n");

	add_exit(NOUTER+"green/g4","southeast",0,0,0);
	add_exit(NOUTER+"green/g8","south",0,0,0);
	add_exit(NOUTER+"green/bar1","southwest","@@msg@@",0,0);
	add_exit(NOUTER+"green/g15","west",0,0,0);
	add_exit(NOUTER+"green/post","northwest","@@msg2@@",0,0);
	add_exit(NOUTER+"green/g19","north",0,0,0);
	add_exit(NOUTER+"green/g6","east",0,0,0);

	reset_room();
}

int
msg()
{
	write("You step into the bar.\n");
	return 0;
}

int
msg2()
{
	write("You step into the post office.\n");
	return 0;
}
