/*
 Bounty hunters training room,
 by Udana 05/06
 temp also join room.
*/

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../bhunters.h"
#include <files.h>


inherit BHROOM + "bhroom";

void add_skills()
{
	create_skill_raise();
	sk_add_train(SS_HUNTING, "hunt for a living", "hunting", 0, 50);
	sk_add_train(SS_SET_TRAP, "set traps", "set traps", 0, 75);
}

string room_long()
{
	return "If not for a chest against the wall, and few personal items on the table you'd guess this room "+
		"is free.\n";
}

public void create_bhroom()
{
	add_exit(BHROOM + "corridor1", "east", 0, 1, 0);
	add_npc(BHNPC + "karl");
	add_item("chest", "Small, wooden chest, standing against the wall, by the window. It's closed.\n");
}