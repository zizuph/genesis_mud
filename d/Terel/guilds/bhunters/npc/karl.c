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
		 ([ "trigger mechanism" : TRAP_COMPONENTS + "trigger",
		"poisoned dart" : TRAP_COMPONENTS + "dart",
		"copper wire" : TRAP_COMPONENTS + "wire",
		"can of pepper" : TRAP_COMPONENTS + "pepper"]),
		([ "trigger mechanism" : 1,
		"poisoned dart" : 2,
		"copper wire" : 1,
		"can of pepper" : 1])
		});
}

void create_keeper()
{
	set_name("karl");
	set_living_name("karl");
	set_title("Zarevko, Paid Assasin of Last");
	set_adj(({"tall", "silent"}));
	set_long(" Tall, muscular man, from his untied clothing and brtistly chin you'd guess he's one of " +
		"hunters, Last is full of this time of year. But there is something about his eyes telling you he's "+
		"more then just that.\n");
    
	set_gender(0);
	default_config_npc(150 + random(40));

	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_PARRY, 60);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_BLIND_COMBAT, 100);
  
	set_hp(query_max_hp());
	add_ask(({"dartgun", "dartgun trap", "blowpipe"}), "@@answer");
	
	enable_intro();
	add_act("say Yes.. I might know a thing or two about traps.");
	add_act("say Come on, spit it out, I haven't got all day.");
	add_act("yawn");
  
}

string answer()
{
	command("Planning an assasination are we? Setting a dartgun trap isn't "+
		"as difficult as you might think. All you need is a trigger mechanism, a blowpipe and some kind of missile. "+
		"It's all about finding the correct angle for the blowpipe really.");
	return "";
}

string trap_answer()
{
	command("say Yes indeed I have some knowledge in this subject. My personal favorite is a dartgun trap. I can tell you how to "+
		"set one yourself.");
	return "";
}

string components_answer()
{
	command("say Sure, I can sell you some of my personal stock, use 'list' if you want to see it.");
	return "";
}

