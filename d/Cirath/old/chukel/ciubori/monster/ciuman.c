/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/ciuman.c
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
  	set_name("bengt");
  	set_race_name("human");
  	set_gender(0);

  	set_adj("ciubori");
 	set_short("ciubori man");
  	set_pshort("ciubori men");
  
  	set_long("This is one of the many citizens of Ci'u'bori. He looks normal.\n");

  	set_stats(({ 10 + random(50), 10 + random(50), 10 + random(50), 10 + random(30), 10 + random(30),50}));
  	set_skill(SS_WEP_KNIFE, 20 + random(20));
  	set_skill(SS_DEFENCE, 30 + random(20));
  	set_skill(SS_PARRY, 30 + random(10));

  	set_alignment(50 + random(50));

  	set_act_time(6);
  	add_act("smile");
  	add_act("ponder Good times again");
  	add_act("shake all");
  	set_chat_time(4);
  	add_chat("Welcome to Ci'u'bori!");
  	add_chat("Hope you like it here, I do");
  	set_cchat_time(6);
  	add_cchat("Please don't kill me, I have a wife and six children to feed!");
  	add_cchat("Help me!");
  	set_cact_time(6);
  	add_cact("sob");
  	add_cact("sulk");
}

query_knight_prestige(){return -100;}

void
arm_me()
{  
  	//if (random(2) == 0) clone_object(CIU_ARM + "ciucloak")->move(TO);
  	//else clone_object(CIU_ARM + "ciupullover")->move(TO);
  	MONEY_MAKE_SC(random(12)+12)->move(TO,1);
  	//clone_object(CIU_ARM + "ciutrousers")->move(TO);
  	clone_object(CIU_WEP + "ciuknife")->move(TO);
  	command("wear all");
  	command("wield all");

 
}
