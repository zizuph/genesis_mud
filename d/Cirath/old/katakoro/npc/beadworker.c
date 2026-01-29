/*
* Created by: Chaos
* Date: 17 April 1995
*
* File: /d/Cirath/katakoro/npc/beadworker.c
* Comments: Beadworker   ,edited by Luther Sept 2001
*/
 
#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>

void
create_monster()
{
   	set_name("beadworker");
	set_race_name("human");
   	set_adj("weary");
   	add_adj("squinty-eyed");
   	set_long("This is the beadworker of the Khahan's camp, he has "+
		"spent many years at this task and is quite skilled at "+
		"shaping just about anything into finely detailed beads. "+
		"Because of the many years of detailed work, his eyes are "+
		"constantly squinted.\n");
	
	add_prop(LIVE_I_NEVERKNOWN, 1);
   	set_stats(({30,45,20,15,15,25}));
   	set_skill(SS_WEP_KNIFE,20);
   	set_skill(SS_DEFENCE,23);
	set_alignment(random(100) - 50);
	
}

void
arm_me()
{
   	MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   	clone_object(KAT_ARM + "avgkalat")->move(TO);
   	clone_object(KAT_WEP + "avgknife")->move(TO);
   	command("wield all");
   	command("wear all");
}

