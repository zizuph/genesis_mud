/*
* Created by: Chaos
* Date: 11 July 1995
*
* File: /d/Cirath/katakoro/npc/woman.c
* Comments: woman, Code originally created by Serpine  ,edited by Luther Sept 2001
*/

#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#include <money.h>

#define RNDADJ ({"sad", "tired", "ugly", "pathetic", "dirty", "hungry"}) [random(6)]

void
create_monster()
{
    	set_adj("weathered");
    	add_adj(RNDADJ);
    	set_race_name("human");
    	set_name("woman");
    	set_long  ("This is one of the many residents of the Khahan's "+
		"main encampment.\n");
    	
    	set_stats(({10,10,10,10,10,10}));
    	add_prop (LIVE_I_NEVERKNOWN, 1);
    	set_act_time(8);
    	add_act("sigh");
    	add_act("ponder");
    	add_act("emote looks somewhat afraid of you.");
    	add_act("say Now that the weather is nice, the Khahan's army is bound "+ 
		"to move");
    	set_gender(1);
    	set_alignment(random(100));
    	set_skill(SS_WEP_KNIFE, 10);
    	set_skill(SS_DEFENCE, 5);
}

void
arm_me()
{    
	clone_object(KAT_WEP + "avgknife.c")->move(TO);
    	command("wield all");
	clone_object(KAT_ARM + "avgkalat.c")->move(TO);
    	command("wear all");
}
