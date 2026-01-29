/* Kitchen on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
	bring_room_mob("slave", TYR_NPC+"jailslav.c", 2);
}

void
create_room()
{
	set_short("kitchen");
	set_long("The east wall is filled with different kinds of pots and "
		+"saucepans. A giant stove is centered on the west wall. The "
		+"rest of the room is filled with benches, cupboards and "
		+"miscellaneous storages. A bunch of cooks is preparing food "
		+"and drinks, you feel like you are in the way. Knifes and "
		+"various kitchen tools hangs on the east wall together with "
		+"with the pots. It smells rather good in here, you can feel "
		+"your stomache grumble of hunger.\n");

	add_item("cooks", "They are running up and down, prepearing some kind "
		+"of food. They look very busy.\n");

	add_item("east wall", "It is totaly filled with various pots and "
		+"saucepans. One section tough, of the wall, is filled with "
		+"knifes, spatulas, ladles and a hugh of other kitchen"
		+"wares.\n");

	add_item(({"west wall", "stove", "giant stove"}), "The giant stove "
		+"nearly takes up the whole west wall. There is only some "
		+"small cupboards and shelves on both sides of it. The stove "
		+"it self is full of stains and old left-overs. All this have "
		+"made the stove it self black and rusty, it is certainly not "
		+"the original colour. The stove is big enough to cook food "
		+"to a huge bunch of people. Both the prisoners and the "
		+"guards food is made on it.\n");

	add_item(({"pots", "saucepans"}), "A huge variety of pots and pans "
		+"hangs on the east wall.\n");

	add_item(({"benches", "cupboards", "storages", "shelves"}), "On the "
		+"shelves and benches you can see different kinds of food "
		+"ingredients. It is easy to seperate the guards food and the "
		+"food that the prisoners is going to have. The prisoners "
		+"food looks all but eatable. You don't dare to look into "
		+"the cupboards while the chef is standing here.\n");

	INSIDE

	add_exit(TYR_JAIL + "diningh.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail1_3.c", "north", 0,1);
        reset_room();
}
