/*                              */
/*    A goblin, by Rico. It     */
/*    uses equipment made by    */
/*    Antharanos.   26.01.94    */
/*                              */

inherit "/d/Kalad/std/monster";

#include "/d/Kalad/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>

create_monster()
{
   ::create_monster();
   
   set_name("gobboda");
   set_race_name("goblin");
   set_adj(({ "scummy", "slimy" }));
   
   set_long("This slimy, scumsucking goblin is repulsive! "+
      "He wanders around the market seeking out easy prey "+
      "and corpses to loot. You think that you might puke "+
      "if you have to put up with his stench much more. "+
      "\n");
   
   set_stats(({ 40, 50, 60, 20, 20, 45 }));

   set_random_move(90);
   
   set_alignment(-300);
   set_knight_prestige(50);
   
   set_skill(SS_WEP_AXE, 40);
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_PARRY, 35);
   set_skill(SS_AWARENESS, 30);
   set_skill(SS_PICK_POCKET, 40);
   
   set_act_time(4);
   add_act("growl all");
   add_act("glare all");
   add_act("rsay Anybody wanna scrap?");
   
   set_cact_time(3);
   add_cact("emote stares at you so intently you think "+
      "that he might strain his brain!");
   add_cact("rsay Ah goin ta eatcha after ah killz ya!");
   
   add_prop(LIVE_I_SEE_DARK,20);
   
   set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
   object wep,arm;
   
   seteuid(getuid(this_object()));
   
   arm = clone_object("/d/Kalad/common/wild/pass/arm/tgbelt");
   arm -> move(TO);
   
   arm = clone_object("/d/Kalad/common/wild/pass/obj/tbag");
   arm -> move(TO);
   
   command("wear all");
   
   wep = clone_object("/d/Kalad/common/wild/pass/wep/tgaxe");
   wep -> move(TO);
   
   command("wield all");
   
   MONEY_MAKE_SC(random(20))->move(TO, 1);
   MONEY_MAKE_CC(random(25))->move(TO, 1);
}

void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("rsay Die, " + ob->query_race_name() + " meat!");
      command("kill " + lower_case(ob->query_real_name()));   
   }
}



