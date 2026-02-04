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
	sk_add_train(SS_AWARENESS, "spot hidden prey", "awareness", 0, 60);
	sk_add_train(SS_FR_TRAP, "handle traps already set", "find and remove traps", 0, 60);
}

string room_long()
{
	return "This room is filled with all kinds of mysterious objects. Some glass apparatus of unknown purpose "+
		"is set on the table, and entire floor is covered with wooden boxes filled with stuff you can't even name.\n";
}

public void create_bhroom()
{
	add_exit(BHROOM + "corridor2", "west", 0, 1, 0);
	add_npc(BHNPC + "ivan");
	add_item(({"apparatus", "glass apparatus"}), "An intriguing mechanism of glass pipes and containers.\n");
	add_item(({"boxes", "wooden boxes"}), "Wooden boxes filled with vials, jars, and pieces of metal of disturbing "+
		"shapes.\n");	
}