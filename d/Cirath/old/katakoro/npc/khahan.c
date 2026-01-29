/*
* Created by: Chaos
* Date: 15 March 1995
*
* File: /d/Cirath/katakoro/npc/khahan.c
* Comments: Khahan   ,edited by Luther Sept 2001
*/

#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>

void
create_monster()
{
	set_name("khahan");
	set_race_name("human");
	set_adj("impressive");
	add_adj("dark-eyed");
	set_long("This is the Khahan of of the endless wastes. He is "+
		"short man, but still an imposing figure. From the scars "+
		"on his face it is obvious that he is not a stranger to "+
		"battle. He wears his hear long, similar to that of the "+
		"men in his army, and has similarly shaved the crown of "+
		"his head. For a man that wield such power, he seems "+
		"rather average looking.\n");

	set_stats(({140,120,140,90,100,150}));
	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_skill(SS_WEP_SWORD,85);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);
	set_skill(SS_PARRY,85);
	set_skill(SS_2H_COMBAT,83);

}

void
arm_me()
{
	MONEY_MAKE_SC(random(25)+1)->move(TO,1);
	clone_object(KAT_ARM + "jacket")->move(TO);
	clone_object(KAT_ARM + "robe")->move(TO);
	clone_object(KAT_ARM + "kkupba")->move(TO);
 	clone_object(KAT_WEP + "knife")->move(TO);
	clone_object(KAT_WEP + "khansword")->move(TO);
	command("wear all");
	command("wield all");
}

