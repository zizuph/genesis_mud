/*
**Dwarven Mining Settlement Cave Base
** Created By Leia
** March 23, 2006
*/

#include "/d/Shire/sys/defs.h";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/cmd/std/command_driver";
inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";

string var;
string descrip_var;

string set_random_items()
{
	switch(random(10))
	{
		case 0:
			var = "cart";
			add_item(({"cart", "mining cart", "empty mining cart", "empty cart"}),
				"This is a typical mining cart. Is is large and rectangular and is " +
				"big enough to hold many gems or pieces of ore.\n");
			descrip_var = "There is an empty mining cart here.";
			break;
		case 1:
			var = "pile";
			add_item(({"pile", "pile of gems", "gems"}), "This is a large pile of " +
				"sparkling gems. There seems to be a hundred gems of every " +
				"color. These are most likely someone else's gems, so you better not " +
				"take any!\n");
			descrip_var = "There is a pile of gems here.";
			break;
		case 2:
			var = "pile";
			add_item(({"pile", "pile of ore", "ore"}), "This is a large pile of " +
				"ore. There are many chunks of every kind, " +
				"of metal. This is most likely someone else's collection for the " +
				"day, so you better not take any!\n");
			descrip_var = "There is a pile of ore here.";
			break;
		case 3:
			var = "tools";
			add_item(({"tools", "broken tools", "tool", "broken tool"}), "These are some broken mining " +
				"picks. There are several broken picks of varying sizes that have " +
				"clearly been put to a lot of use.\n");
			descrip_var = "There are some broken tools laying here.";
			break;
		case 4:
			var = "debris";
			add_item(({"debris", "pile of debris"}),  "This is a pile of rock debris. " +
				"It has likely spilled out of a cart carrying debris up from the mine. " +
				"Maybe someone will be along soon to clean it up.\n");
			descrip_var = "There is a pile of debris here.";
			break;
		case 5:
			var = "cart";
			add_item(({"cart", "mining cart", "full mining cart", "full cart"}), "This " +
				"is a really full mining cart. It is filled with both gems and ore, and " +
				"looks to be the haul from a team of workers.\n");
			descrip_var = "There is a full mining cart here.";
			break;
		case 6:
			var = "toolbox";
			add_item(({"toolbox", "box"}), "This is a toolbox used for holding " +
				"tools for mining. Someone probably sat it down and forgot to grab it. " +
				"They will probably be back for it soon.\n");
			descrip_var = "There is a toolbox here.";
			break;
		case 7:
			var = "sifter";
			add_item(({"sifter"}), "This is a sifter. Someone has set this sifter up " +
				"to sort through the debris that they have collected and find any " +
				"ore or gems hidden within.\n");
			descrip_var = "There is a sifter here.";
			break;
		case 8:
			var = "wheelbarrow";
			add_item(({"wheelbarrow"}), "This is a sturdy wheelbarrow. It has likely " +
				"been being used to transport debris and valuables up from the mine. Better " +
				"leave it here in case the owner returns.\n");
			descrip_var = "There is a wheelbarrow here.";
			break;
		case 9:
			var = "crates";
			add_item(({"crates", "boxes", "box"}), "These boxes are stamped with names of various " +
				"lands and destinations. They are most likely waiting to be picked up and " +
				"transported to buyers from all over.\n");
			descrip_var = "There are several boxes here.";
			break;
		default:
			descrip_var = "Uh oh! Something's buggy! Better report it!";
	}
}

void test_random_items()
{
	switch(random(3))
	{
		case 0:
			set_random_items();
			break;
		case 1:
			descrip_var = "";
			break;
		case 2:
			descrip_var = "";
			break;
		
	}
}

void set_add_rtells()
{
	set_room_tell_time(90 + random(15));
	add_room_tell("A warm air current passes through, bringing a small amount of fresh air into the area.\n");
	add_room_tell("You hear the faint chirping of a canary from somewhere nearby. Sounds like all is safe, for now.\n");
	add_room_tell("A dwarf runs by pushing a wheelbarrow, eager to get to his destination.\n");
	add_room_tell("You hear the clinking of a cart running down the tracks. Quickly, you dodge out of its way.\n");
	add_room_tell("Somewhere nearby you hear a dwarf whistling. Time flies when you whistle while you work.\n");
	add_room_tell("There is a loug crashing sound nearby, followed closely by the bickering of two dwarves.\n");
}