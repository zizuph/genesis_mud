/*
* Created by: Chaos
* Date: 15 March 1995
*
* File: /d/Cirath/katakoro/npc/kashik.c
* Comments: Kashik Guards   ,edited by Luther Sept 2001
*/

#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>
#include "/sys/formulas.h"

void
create_monster()
{
   	set_name("kashik");
	set_race_name("human");
	set_adj("battle-hardened");
	set_long("This is a member of the Khahan's elite guard known "+
		"as the Kashik. They have been chosen for thier "+
		"exceptional skill and ability to protect the life "+
		"of their Khahan. His hair is worn in long braids, "+
		"bound with silver disks and tassels of blue yarn.\n");

   	set_stats(({110,100,110,90,80,110}));
   	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_skill(SS_WEP_SWORD,85);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);
   	set_alignment(random(100) - 50);
}

void
arm_me()
{
   	MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   	clone_object(KAT_WEP + "ksword")->move(TO);
   	clone_object(KAT_ARM + "kalat1")->move(TO);
	command("wear all");
	command("wield all");
}

