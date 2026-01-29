/*
* Created by: Chaos
* Date: 15 March 1995
*
* File: /d/Cirath/katakoro/npc/eguard.c
* Comments: Empress' Guardsr   ,edited by Luther Sept 2001
*/

#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>
#include "/d/Cirath/common/teamfnc.h"

void
create_monster ()  
{
	set_name("eguard");
	set_race_name("human");
	set_adj("battle-hardened");
	set_long("This is a member of the Empress' elite guard. "+
		"They have been chosen for thier "+
		"exceptional skill and ability to protect the life "+
		"of their Empress. His hair is worn in long braids, "+
		"bound with silver disks and tassels of blue yarn.\n");
   	set_stats(({105,105,100,90,90,110}));
   	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_skill(SS_WEP_SWORD,85);
	set_skill(SS_DEFENCE,85);
	set_skill(SS_AWARENESS,60);
   	set_alignment(random(100) - 50);

}

void
arm_me ()
{
   	MONEY_MAKE_SC(random(10)+1)->move(TO,1);
   	//clone_object(KAT_ARM + "kalat3.c")->move(TO);
   	//clone_object(KAT_WEP + "ksword.c")->move(TO);
	command("wear all");
	command("wield all");
}

