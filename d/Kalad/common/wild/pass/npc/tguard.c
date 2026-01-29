/* 
 * /d/Kalad/common/wild/pass/npc/tguard.c
 * Purpose    : A troglodyte guard
 * Located    : /d/Kalad/common/wild/pass/underdark/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("guard");
   set_race_name("troglodyte");
   set_adj("carnivorous");
   set_short("troglodyte guard");
   set_long("A reptilian humanoid that stands roughly six feet tall. Its "+
      "completely covered in leathery scales and has a toothy lizard-like head. "+
      "The greyish-brown creature has a large fin running from the top of "+
      "its head down along its back.\n");
   set_stats(({60,55,60,40,40,65}));
   set_alignment(-50);
   set_skill(SS_WEP_AXE,70);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,40);
   set_act_time(6);
   add_act("growl all");
   add_act("glare all");
   add_act("rsay Fresh meat!");
   set_cact_time(3);
   add_cact("emote looks like he wants to eat you!");
   add_cact("rsay Me eat you for food!");
   set_knight_prestige(50);
   add_prop(LIVE_I_SEE_DARK,10);
   set_alarm(1.0,0.0,"arm_me");
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
   MONEY_MAKE_SC(random(20))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("rsay Die, " + ob->query_race_name() + " meat!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
