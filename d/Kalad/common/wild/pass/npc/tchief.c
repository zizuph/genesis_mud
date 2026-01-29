/* 
 * /d/Kalad/common/wild/pass/npc/tchief.c
 * Purpose    : A troglodyte chieftan
 * Located    : /d/kalad/common/wild/pass/underdark/
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
   set_name("chieftain");
   set_race_name("troglodyte");
   set_adj("massive");
   set_short("troglodyte chieftain");
   set_long("A massive reptilian humanoid standing just over seven feet tall. It is "+
      "completely covered in leathery scales and has a toothy lizard-like head. "+
      "The greyish-brown creature has a large fin running from the top of "+
      "its head down along its back. This is clearly the leader of the "+
      "troglodytes, for he is larger and stronger than all of the others.\n");
   set_stats(({80,70,80,50,50,75}));
   set_alignment(-75);
   set_skill(SS_WEP_SWORD,80);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,40);
   set_act_time(6);
   add_act("growl all");
   add_act("glare all");
   add_act("snarl all");
   add_act("rsay Ahh, now me have more meat to play with.");
   set_cact_time(3);
   add_cact("emote looks like he's going to eat you alive!");
   add_cact("rsay Me kill you, then have you as food!");
   set_knight_prestige(75);
   add_prop(LIVE_I_SEE_DARK,10);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/wild/pass/arm/tcbelt");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/tcarmour");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/obj/tbag");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/wild/pass/wep/tcsword");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("rsay Now I eat you for dinner, stupid " + ob->query_race_name() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
