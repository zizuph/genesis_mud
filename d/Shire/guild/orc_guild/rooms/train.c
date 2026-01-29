
/* 
	*Training room of the orc race guild cave
	*Altrus, May 2005
*/
#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit "/d/Shire/std/room";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

void set_up_skills();

void create_shire_room()
{
	set_short("A small side chamber");

	set_long(short() + ". The walls have been cut from the surrounding stone, very crudely. This is where orcs of this clan come to get their training. There are weapons strewn about the floor, and several wounded orcs occupy the fringe of the room. There is a broad stone in the middle of the chamber; it has some writing engraved upon it.\n");
	
	add_item(({"room", "chamber", "side chamber"}), "This room looks to have been completely carved out of the stone of one of the walls of the main passage.\n");
	add_item(({"walls", "stone"}), "The walls are completely carved from the rock, and nearly square.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"orcs", "wounded orcs"}), "These miserable creatures couldn't handle the training, and sit in the darker corners of the room, licking their wounds.\n");
	add_item(({"weapons", "implements"}), "They are junked weapons mostly, chipped and cracked and broken implements used in training.\n");
	add_item(({"corners", "fringe"}), "In the corners your wounded brothers sit and look at you with a mixture of fear and hatred.\n");
	add_item(({"stone", "broad stone", "writing"}), "Try reading the writing on the stone.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_cmd_item("writing","read","@@read_writing@@");
	add_exit("/d/Shire/guild/orc_guild/rooms/passage2", "west");
	
	create_skill_raise();
	create_guild_support();
	set_up_skills();
}

void
init() 
{
	init_skill_raise();
	init_guild_support();
	::init();
}

void
set_up_skills() 
{
	string me;
	
	//the following skills are taxed.
	me = "swing a sword";
	sk_add_train(SS_WEP_SWORD,({ me, me }),    0,0,50 );
	
	me = "fight in the dark";
	sk_add_train(SS_BLIND_COMBAT,({ me, me }),    0,0,50 );
	
	me = "evaluate enemies";
	sk_add_train(SS_APPR_MON,({ me, me }),    0,0,50 );
	
	me = "climb more easily";
	sk_add_train(SS_CLIMB,({ me, me }),       0,0,40 );
	
	me = "know where you are";
	sk_add_train(SS_LOC_SENSE,({ me, me }),   0,0,40 );
	
	me = "perceive your surroundings";
	sk_add_train(SS_AWARENESS,({ me, me }),   0,0,40 );
	
	me = "recognize tracks";
	sk_add_train(SS_TRACKING,({ me, me }),      0,0,50 );
	
	// the following skills are not taxed.       
	me = "defend yourself";
	sk_add_train(SS_DEFENCE,({ me, me }),     0,0,20 );
	
	me = "handle and use knives";
	sk_add_train(SS_WEP_KNIFE,({ me, me }),   0,0,30 );
}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}

string read_writing(string str)
{
	return "\n                      _____\n"+
		"              _____  /     \\_____\n"+
		"             /     \\/            \\____\n"+
		"         ___/ Get these skills beat   \\\n"+
		"      __/        into your head!       \\__\n"+
		"     /                                    \\_\n"+
		"   _/  Sword..........Superior Journeyman   \\\n"+
		"  /    Knife..........Superior Layman        |\n"+
		" |     Defence........Superior Amateur       \\\n"+
		" |     Blindfighting..Superior Journeyman    /\n"+
		"  \\    Appraise enemy.Superior Journeyman    \\\n"+
		"  /    Climb..........Superior Acolyte        \\ \n"+
		" |     Awareness......Superior Acolyte        /\n"+
		"  \\_   Location sense.Superior Acolyte       |\n"+
		"    \\_ Tracking.......Superior Journeyman __/\n"+
		"      \\___                   ____       _/\n"+
		"          \\____/\\        ___/    \\_____/\n"+
		"                 \\______/\n\n";
}
