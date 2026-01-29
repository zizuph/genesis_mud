
/* 
	*A large kitchen in the house of farmer Maggot
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_HOUSE;
inherit "/d/Shire/std/room";

void make_npcs();

object maghob;

void create_shire_room()
{
	set_short("A rather large kitchen");

	set_long(short() + ". Cupboards line almost every inch of the walls; cooking utensils hang from the ceiling over a preparation table; a large stove next to a cooking fire inhabits the southwest corner. As this is a working farm, the hobbits here have forgone the usual dining room one might see in a hobbit-home, and there is a rather long wooden table and benches near the door to the room. The smell of baking pastries is quite prevelant.\n");
	
	add_item(({"kitchen"}), "This is clearly a hobbit's kitchen. And telling from the smells, it is a well used kitchen.\n");
	add_item(({"ceiling"}), "It is very low, barely six feet from the floor.\n");
	add_item(({"walls", "wall"}), "The walls, where open, are used for the sole purpose of storage cupboards.\n");
	add_item(({"floor"}), "Unlike the rest of the house, the floors in here are dusted with flour, crumbs and various other signs of food preparation.\n");
	add_item(({"cupboard", "cupboards"}), "Most of them are closed, but you imagine they must be full of food and ingredients for culinary masterpieces.\n");
	add_item(({"utensils"}), "Mostly pots and pans are hanging from the ceiling.\n");
	add_item(({"pots", "pans"}), "The pots and pans hanging from the ceiling are clean, but look well used.\n");
	add_item(({"table", "tables"}), "There are two tables here, a preparation table and a long wooden table. Which one do you want to look at?\n");
	add_item(({"preparation table"}), "All manner of food preparation must take place here. There are nicks and scratches all over its surface.\n");
	add_item(({"nicks", "scratches", "surface", "marks"}), "They are probably marks left over from long use with a knife. The table is certainly much used.\n");
	add_item(({"long table", "long wooden table", "wooden table"}), "There is nothing on the table right now, but it looks like it has room for at least ten hobbits to a side.\n");
	add_item(({"bench", "benches"}), "They are long benches, made to match the length of the table.\n");
	add_item(({"stove"}), "It is a large stove, and judging from the smells in the kitchen, it is currently being used.\n");
	add_item(({"fire", "cooking fire"}), "There is nothing being cooked over the fire at the moment, but there is a metal frame, which is probably where a cooking pot is hung when in use.\n");
	add_item(({"frame", "metal frame"}), "It looks sturdy. It could probably hold a large pot for boiling water or making stew.\n");
	add_item(({"corner", "southwest corner"}), "The southwest corner has a cooking fire, which looks to be shared with the fireplace in the parlor room.\n");
	
	add_exit(ROOM_DIR + "maggothall02", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void init()
{
	::init();
	add_action("smell_stuff", "smell");
}

void make_npcs()
{
	if(!maghob)
	{
		maghob = clone_object(NPC_DIR + "mrs_maggot");
		maghob->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(maghob->query_nonmet_name()))+ " bustles into the kitchen, looking very busy.\n");
	}
}

int smell_stuff()
{
	TP->catch_msg("You take a deep breath through your nose, and are rewarded with a wonderful smell of baking pastries!\n");
	return 1;
}
