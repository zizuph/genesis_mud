/*
* Created by: Chaos
* Date: 18 April 1995
*
* File: /d/Cirath/katakoro/npc/clothworker.c
* Comments: Clothworker   ,edited by Luther Sept 2001
*/
 
#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>

void
create_monster()
{
   	set_name("clothworker");
	set_race_name("human");
   	set_adj("weary");
   	add_adj("leathery-skinned");
   	set_long("This is the clothworker for the Khahan's tribe. She "+
		"is responsible for the building of the felt rugs nessecary "+
		"in construction of yurts. She also makes the clothing "+
		"worn by the Khahan and his wife, a honor she is quite "+
		"proud of. The many years of her life are visible in her "+
		"leathery skin, a deceptive, but accurate revealer of her "+
		"age.\n");

	add_prop(LIVE_I_NEVERKNOWN, 1);
   	set_gender(1);
   	set_stats(({20,35,15,15,15,15}));
   	set_skill(SS_WEP_KNIFE,16);
   	set_skill(SS_DEFENCE,20);
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

