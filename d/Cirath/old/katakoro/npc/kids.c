/*
* Created by: Chaos
* Date: 11 July 1995
*
* File: /d/Cirath/katakoro/npc/kids.c
* Comments: kids, Original Code by Serpine   ,edited by Luther Sept 2001
*/

#pragma strict_types

inherit "/std/monster";
#include "defs.h"
#define RNDADJ ({"sad", "tired", "ugly", "pathetic", "dirty", "hungry"})[random(6)]

void
create_monster()
{
    	set_adj(RNDADJ);
    	set_name("kid");
    	set_race_name("human");
    	set_long("This is one of the children that makes up the "+
		"civilian portion of the Khahan's camp city. It "+
		"probably belongs to one of the soldiers in the army.\n");
		
    	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_stats(({5,5,5,5,5,5}));
   	set_act_time(8);
    	add_act("sigh");
    	add_act("ponder");
    	add_act("emote looks somewhat afraid of you.");
    	add_act("say Why don't you just leave me alone?");
    	set_gender(random(2));
    	set_alignment(random(75));
}

void
arm_me()
{
    clone_object(KAT_ARM + "avgkalat.c")->move(TO);
    command("wear all");
}
