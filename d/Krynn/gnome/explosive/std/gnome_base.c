/**
* Coded by Louie 2004
* 
* Gnome base
*
* Common gnome stuff for the gnomes who work in the explosives section
* of the gnome colony.  These gnomes are mostly like the regular gnomes,
* except they say a few different things and they have a special attack
* where they lob grenades.
*
* Navarre December 31st 2007.
* Changed int brain to string brain, as add_act VBFC calls should return string
* and not int.
* Also changed "@@brain" to brain, as its the preferred VBFC approach.
*/

#pragma strict_types

#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

inherit M_FILE
inherit "/std/act/action";

/*prototypes*/
void equipme();
string brain();
void miss_throw();
void announce_attack();

/*
* Create
*/
public void
create_krynn_monster()
{
	int i;
	
	remove_prop(NPC_M_NO_ACCEPT_GIVE);
	
	add_name("_explosive_gnome");
	set_race_name("gnome");
	
	add_act(brain);
	
	add_cact("say HeyHaveYouLostYourMind?");
	add_cact("say SomebodyGetTheGuards!I'llStallThem...");
	add_cact("say WhereWasThatFlameThrower?");
	add_cact("shout FireInTheHole!");
	set_act_time(10);
	set_cact_time(5);
	
	for (i = 0; i < 6; i++)
		set_base_stat(i, 15 + random(25));
	
	set_hp(10000);
	set_alignment(100);
	set_all_hitloc_unarmed(10);
	set_knight_prestige(-2);
	
	set_alarm(1.0, 0.0, "equipme");
	set_skill(SS_DEFENSE, 30);
	set_skill(SS_WEP_CLUB, 50);
	set_skill(SS_BLIND_COMBAT, 50);
	set_skill(SS_UNARM_COMBAT, 50);
	NEVERKNOWN;
}

public void
equipme()
{
	seteuid(getuid());
	
	if (!random(4)) 
	{
		clone_object(OLD_GNOME_OBJ+"hammer")->move(TO);
	}
	if (!random(4))
	{
		clone_object(OLD_GNOME_OBJ+"cloak")->move(TO);
	}
	if (!random(4))
	{
		clone_object(OLD_GNOME_OBJ+"helmet")->move(TO);
	}
	command("wear all");
	command("wield hammer");
}

void
attacked_by(object ob)
{
	::attacked_by(ob);
	if ((QRACE(ob) == "gnome") && (!ob->query_npc()))
	{
		command("shout Traitor!  HowDareYouHowCouldYouYouWillSurelyPay!");
		write_file("/d/Krynn/gnome/log/fight.log",ob->short() + " " +
			ob->query_nonmet_name() + "\n");
		say("\nA scuffle breaks out among the gnomes, and one is " +
			"carted off.\n");
		write("\nYour brethren grab you and cast you out of their " +
			"home!\n");
		write("You are now persona non grata among the gnomes.  " +
			"Try helping a gnome in need to redeem yourself.\n");
		TP->move_living("this happy gnomish place..",
			OLD_GNOME+"entrance.c");
		say("\n");
	} else {
		command("say Help! Stop this " + ob->query_nonmet_name() + "!");
	}
	
}

string
brain()
{
	int i;
	string *stuff;
	
	stuff = ({"a hammer", "a spring-loaded whatsit",
		"several large balls of string", "a smoking pair of shoes"});
	
	i = random(5);
	
	if (!i)
	{
		command("says DidYouHearALoudBoomJustNow?");
		command("emote flinches.");
	} else if (i == 1)
	{
		command("say SoonEveryOneWillBeUsingMySteampoweredCatapults!");
		command("say I'llBeFamous!");
		command("emote smiles gnomishly.");
	} else if (i == 2)
	{
		command("say NeedsMoreBellsAndWhistlesAndStuff.");
	} else if (i == 3)
	{
		command("say WhatHappensWhenIPullThisLever?");
		command("grin evil");
	} else 
	{
		tell_room(environment, "A gnome runs by carrying " +
			stuff[random(sizeof(stuff))] + ".\n");
	}
	return "";
}

int
special_attack(object enemy)
{
	object me;
	mixed* hitresult;
	string descrip;
	
	me = TO;
	
	/*10% chance to use special*/
	if (random(10))
	{
		/*continue with normal combat*/
		return 0;
	}
	
	announce_attack();
	
	/*hitresult is the % hurt*/
	hitresult = enemy->hit_me(40, MAGIC_DT, me, -1);
	
	enemy->catch_msg(QCTNAME(me) + " throws a grenade " +
		"at you!\n");
	tell_watcher(QCTNAME(me) + " throws a grenade at " +
		QTNAME(enemy) + "!\n", ({me, enemy}));
		
	if (hitresult[0] < 1)
	{
		enemy->catch_msg("The grenade bounces off of you " +
			"and burns itself up, causing no harm.\n");
	
		tell_watcher("The grenade bounces off of " +
			HIM(enemy) + " and burns itself up, " +
			"causing no harm.\n",
			({me,enemy}));
		set_alarm(1.0,0.0,"miss_throw");
	} 
	else if ((hitresult[0] > 0) && (hitresult[0] < 6))
	{
		descrip = "small";
				
	} 
	else if ((hitresult[0] > 5) && (hitresult[0] < 11))
	{
		descrip = "powerful";
		
	} 
	else if ((hitresult[0] > 10) && (hitresult[0] < 21))
	{	
		descrip = "huge";

	} 
	else {
		descrip = "enormous";
	}
	
	enemy->catch_msg("The grenade detonates, engulfing you in " +
		"a " +descrip+" explosion!\n");
	
	tell_watcher("The grenade detonates, engulfing " +
		HIM(enemy) + " in a "+descrip+" explosion!\n",
		({me,enemy}));

		
	if (enemy->query_hp() <= 0)
	{
		enemy->do_die(me);
		//enemy->catch_msg("You should be dead right now.  0 hps!\n");
	} else
	{
		if (!random(5))
		{
			set_alarm(1.0, 0.0, "miss_throw");
		}
	}
		
	/*return 1 since it was a special combat round*/
	return 1;
	
}

void
miss_throw()
{
	int i;
	i = random(5);
	
	if (i == 1)
	{
		command("say HmmObviouslyNotOneOfMyBetterDesigns.");
	} else if (i == 2)
	{
		command("rolleyes");
		command("say ThrowMeABoneHerePeople.");
	} else if (i == 3)
	{
		command("say WellThatWasQuiteAntiClimatic.");
	} else if (i == 4)
	{
		command("curse");
	}
}

void
announce_attack()
{
	int i;
	i = random(5);
	
	if (i == 1)
	{
		command("shout FireInTheHole!");
	} else if (i == 2)
	{
		command("say HowAboutALittleFire,Scarecrow?");
		command("cackle mani");
	} else if (i == 3)
	{
		command("shout Incoming!");
	} else if (i == 4)
	{
		command("say One..Two..Five!  OhWaitThreeIMeanThree!");
	}
}
