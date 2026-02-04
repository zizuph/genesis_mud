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
	sk_add_train(SS_LOC_SENSE, "know where the north is", "location sense", 0, 50);
	sk_add_train(SS_CLIMB, "climb", "climb", 0, 40);
	sk_add_train(SS_TRACKING, "find prey by its tracks", "tracking", 0, 60);
}

string room_long()
{
	return "This room looks like it has been inhabitied by the same person for quite some "+
		"time now. From number of animal trophies and weapons on the walls you'd guess said "+
		"person is a hunter. And not very clean one considering the smell of this place.\n";
}

public void create_bhroom()
{
	add_exit(BHROOM + "corridor1", "west", 0, 1, 0);
	add_npc(BHNPC + "boris");
	add_item(({"trophy", "trophies"}), "Deers, mooses and bears stares into space with their blind eyes.\n");
	add_item("weapons", "Knives and axes in all shapes and colours are hanging on the wall, giving this place "+
		"a bit creepy look.\n");
}