inherit "/d/Shire/orcmaker/orcmaker";
inherit "/d/Shire/lib/kill_logger";
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/common/make_money.h"

/* Gorgun, orc, wielder of Leech, leader of camp in Hsqwin Mountain
   5 April 1994 by Mayhem  
 */

void drink_up();
 
void create_monster()
{
  ::create_monster();
  remove_adj(query_adj());
  remove_adj(query_adj());
  set_adj(({"filthy","long-armed"}));
  set_name("gorgun");
  set_race_name("orc");
  set_long("This filthy, long-armed orc has an air of command about "+
    "him. While his bearing could never be described as regal or noble, "+
    "it still projects power and the impression of impatience and "+
    "strength.\n");
  set_alignment(-300-random(101));
  set_attack_chance(0);
  default_config_npc(70+random(6));
  set_base_stat(SS_STR, 200+random(30));
  set_base_stat(SS_CON,150+random(21));
  set_base_stat(SS_DEX,140+random(11));
  set_base_stat(SS_DIS,90+random(10));

  set_skill(SS_WEP_SWORD,90+random(11));
  set_skill(SS_DEFENCE,80+random(11));
  set_skill(SS_PARRY,75+random(16));
  set_skill(SS_AWARENESS,70+random(11));
  set_skill(SS_2H_COMBAT,75+random(26));
  set_skill(SS_BLIND_COMBAT,50+random(31));
  set_skill(SS_WEP_KNIFE, 60 + random(10));
   set_skill(SS_WEP_AXE, 40 + random(15));
   set_skill(SS_WEP_POLEARM, 75 + random(5));

  add_chat("Where is that damned mage, he was supposed to be "+
    "here days ago.");
  add_chat("You there, find my lieutenant, I have a job for him.");
   add_act("wield scimitar");

   add_prop(LIVE_I_QUICKNESS, 200);
   add_prop(LIVE_I_SEE_DARK, 4);
  MAKE_MONEY;
  make_gold(12);
set_kill_log_name("gorgun");
set_kill_log_size(50000);
  set_alarm(1.0,0.0,"arm_me");
}

void arm_me()
{
  object key,wep,arm,drink;
  int i;
  seteuid(getuid(TO));

  key=clone_object(GREEN_DIR+"obj/hchest_key");
  key->move(TO);
  arm = clone_object(GREEN_DIR + "arm/hhelm");
  arm->move(TO);
  arm = clone_object(GREEN_DIR + "arm/hplate");
  arm->move(TO);
  arm = clone_object(GREEN_DIR + "arm/hboots");
  arm->move(TO);
  command("wear all");
  command("lower visor");
  wep=clone_object(GREEN_DIR + "wep/magebane");
  wep->move(TO);
  command("wield all");
  for (i = 0; i < 20; i++)
  {
    drink = clone_object("/d/Shire/moria/obj/orcdrink");
    drink->move(TO);
  }
  set_alarm(itof(random(10)), 0.0, &drink_up());
  command("say Prepare to eat scimitar, scum.");

  set_alarm(0.5,0.0,"do_chest");
}


void
drink_up()
{
  command("drink all");
}
 
void do_chest()
{
  command("get chest");
  command("put coins in chest");
  command("close chest");
  command("lock chest with key");
//  command("drop chest");
}
 
void
attacked_by(object player)
{
  set_alarm(60.0, 0.0, &drink_up());
}
