/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/ciuwoman.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/monster";
inherit "/std/act/action";

#include "defs.h"
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include </sys/money.h>

void
create_monster()
{
  	set_name("augusta");
  	set_race_name("human");
  	set_gender(1);

  	set_adj("ciubori");
  	set_short("ciubori woman");
  	set_pshort("ciubori women");
  
  	set_long("This is one of the many citizens of Ci'u'bori. She looks normal.\n");

  	set_stats(({ random(30), random(50), random(30), random(30), random(30),50}));
  	set_skill(SS_DEFENCE, 30 + random(20));
  	set_skill(SS_UNARM_COMBAT,20 + random(20));

  	set_alignment(50 + random(50));

  	set_act_time(6);
  	add_act("curtsey");
  	add_act("strut");
  	add_act("greet all");
  	add_act("think knitting");
  	set_chat_time(4);
  	add_chat("Welcome to Ci'u'bori!");
  	add_chat("Don't you like knitting? I like it much.");
  	set_cchat_time(6);
  	add_cchat("I will call my husband!");
  	add_cchat("Help me!");
  	set_cact_time(6);
  	add_cact("emote whines helplessly.");
  	add_cact("sob");
}

query_knight_prestige(){return -100;}

void
arm_me()
{
  	//if (random(2) == 0) clone_object(CIU_ARM + "ciucloak")->move(TO);
  	//else clone_object(CIU_ARM + "ciupullover")->move(TO);
  	MONEY_MAKE_CC(random(10)+2)->move(TO,1);
  	//clone_object(CIU_ARM + "ciuskirt")->move(TO);
  	command("wear all");
}
