/*
  Shopkeeper of the trap store.
    by Udana, 06/06
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../bhunters.h"

inherit BHNPC + "bhkeeper";

public mapping *query_components()
{
	return ({
		 ([ "blowpipe" : TRAP_COMPONENTS + "blowpipe",
		"foothold" : TRAP_COMPONENTS + "snare",
		"small iron ball" : TRAP_COMPONENTS + "ball",
		"medium iron ball" : TRAP_COMPONENTS + "ball",
		"large iron ball" : TRAP_COMPONENTS + "ball",
		"shovel" : TRAP_COMPONENTS + "shovel",
		"bucket of paint" : TRAP_COMPONENTS + "paint",
		"steel chain" : TRAP_COMPONENTS + "chain"]),
		([ "blowpipe" : 1,
		"foothold" : 2,
		"small iron ball" : 1,
		"medium iron ball" : 2,
		"large iron ball" : 3,
		"shovel" : 2,
		"bucket of paint" : 1,
		"steel chain" : 1])
		});
}


void create_keeper()
{
	set_name("boris");
	set_living_name("boris");
	set_title("Kursov, Bounty Hunter of Last");
	set_adj(({"short", "massive"}));
	set_short("short massive male human");
	set_long(" Massive, muscular human standing before you looks a bit frightening. Pale, with sparse beard " +
		"on scarred and deformed face. He's probably well past his 40s, but word 'experienced' seems "+
		"more accurate then 'old' in his case.\n");
    
	set_gender(0);
	default_config_npc(120 + random(30));

	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_PARRY, 60);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_BLIND_COMBAT, 100);
  
	set_hp(query_max_hp());
	add_ask(({"foothold", "foothold trap"}), "@@answer");
	
	enable_intro();
	add_act("say Traps, now that's a tricky buisness, but worry not, I can help.");
	add_act("say Ahh, I can't wait to leave this city and go hunting again.");
	add_act("scratch");
  
}

string answer()
{
	command("say Oh.. this one is a beauty. You'll need a snare of a foothold, a chain " +
		"and something heavy, an iron ball, like one of those I have, would be just fine. Then it's just setting the snare, "+
		"and chaining it to the ball.");
	return "";
}

string trap_answer()
{
	command("say Trap asks you? I know of traps, aye. I can sell you all the components you need to " +
		"to catch your rabbit. I can also tell you how to make me favorite one - a foothold.");
	return "";
}

string components_answer()
{
	command("say Aye, I sell them, you can 'list' what I have if you're in need of one.");
	return "";
}

