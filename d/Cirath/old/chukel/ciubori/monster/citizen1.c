/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/monster/citizen1.c
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
  set_name("goran");
  set_race_name("human");
  set_gender(0);

  set_adj("wealthy");
  set_short("wealthy citizen");
  set_long("This is one of the many citizens of Ci'u'bori. He looks very wealthy.\n");

  set_stats(({ 40, 40, 40, 30, 30, 50}));
  set_skill(SS_WEP_KNIFE, 30 + random(10));
  set_skill(SS_DEFENCE, 30 + random(20));
  set_skill(SS_PARRY, 30 + random(10));

  set_alignment(50 + random(50));

  set_all_hitloc_unarmed(10); 

  set_act_time(6);
  add_act("yawn");
  add_act("emote starts counting his coins.");
  add_act("think business");
  set_chat_time(4);
  add_chat("What are you doing here stranger?");
  add_chat("I hope that you're not in the same trade as I, for your sake I mean!");
  set_cchat_time(6);
  add_cchat("You will never get hold of my gold!");
  add_cchat("You dirty...dirty... ... son of a ... hmmm...");
  set_cact_time(6);
  add_cact("shout HELP! HELP! I'm being attacked!!");
  add_cact("cry");
}

query_knight_prestige(){return -100;}

void
arm_me()
{
  MONEY_MAKE_SC(random(12)+5)->move(TO,1);
  clone_object(CIU_ARM + "ciuarmor")->move(TO);
  clone_object(CIU_ARM + "ciuhelm")->move(TO);
  clone_object(CIU_ARM + "ciuboots")->move(TO);
  clone_object(CIU_WEP + "ciuknife")->move(TO);

  command("wear all");
  command("wield all");

}

