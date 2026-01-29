inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("arim");
   add_name("guard");
   set_race_name("human");
   set_adj("company");
   set_short("company guard");
   set_long("This man is one of the guardsmen of the powerful and wealthy "+
      "trading company. He doesn't look too happy to see you here.\n");
   set_stats(({80,85,80,60,60,85}));
   set_alignment(0);
   set_skill(SS_WEP_POLEARM,100);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_AWARENESS,60);
   set_act_time(6);
   add_act("emote frowns unhappily at you.");
   add_act(({"poke all","say Leave before someone gets hurt."}));
   add_act("say You're not supposed to be here.");
   set_cact_time(3);
   add_cact("say Now I'm going to hurt you!");
   add_cact("emote looks like he's going to hurt you.");
   add_cact("shout Guards! An intruder!");
   add_speak("Only company members are allowed to pass.\n");
   set_knight_prestige(0);
   set_title("the Company Guardsman");
   set_default_answer("The company guard says: What was that?\n");
   add_ask(({"passage","pass","passing"}),"The company guard says: Noone "+
      "can enter the company building. Only company members are allowed "+
      "inside.\n");
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/caravan/arm/tcgplate");
   arm -> move(this_object());
   arm = clone_object("/d/Kalad/common/caravan/arm/tcghelm");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/caravan/wep/tcghalb");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(this_object(),1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("gasp");
      command("say Die! Enemy of the Company!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
void init_living()
{
   ::init_living();
   add_action("pass","pass");
}
pass()
{
   write("You explain to the guard that you are here to trade.\n");
   write("The company guard allows you to pass.\n");
   say(QCTNAME(TP) + " says something to the guard, who then allows "+ TP->query_objective() + " to pass.\n");
   TP->move_living("north into the building","/d/Kalad/common/caravan/company/s2");
   return 1;
}
