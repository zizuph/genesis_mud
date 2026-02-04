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
		 ([ "magic alarm" : TRAP_COMPONENTS + "alarm",
		"battery charge" : TRAP_COMPONENTS + "battery"]),
		([ "magic alarm" : 1,
		"battery charge" : 2])
		});
}

void create_keeper()
{
	set_name("ivan");
	set_living_name("ivan");
	set_title("Kursov, Supreme Hunter of the Man and Beasts");
	set_adj(({"old", "mysterious"}));
	set_long("You'd say this man have a look of a wizard, or some kind of noble. But you can't imagine "+
		"what would either wizard or high-born could do in such place.\n");
    
	set_gender(0);
	default_config_npc(100 + random(20));

	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_PARRY, 60);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_BLIND_COMBAT, 100);
  
	set_hp(query_max_hp());
	add_ask(({"alarm", "magic alarm"}), "@@answer");
	
	enable_intro();
	add_act("say Come, friend, I'm listening.");
	add_act("say Have you met my brother Boris already?");
	add_act("hum");
  
}

string answer()
{
	command("say Oh yes, magic alarm is one of my greatest inventions. It solves, the main "+
		"problem one encounters when hunting with traps. How do you tell if something have triggered the "+
		"trap already? Well, attach one of my alarms to the trap, and worry no longer.");
	return "";
}

string trap_answer()
{
	command("say As you can see I'm no unshaved trapper, but you'd be supprised by the level of sophistication some "+
		"of traps might have. Personally I focus on those related to magic. I can tell you of my latest invention - "+
		"a magic alarm.");
	return "";
}

string components_answer()
{
	command("say Yes, I do hold some of the rarest components here. You can 'list' what I have if you're interessted.");
	return "";
}

