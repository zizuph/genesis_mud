inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"
int str;
int dex;
int con;

/* by Antharanos */
/* 2017-06-03 Malus: Removed name, add LIVE_I_NEVERKNOWN */

void
create_monster()
{
   add_name("militiaman");
   set_race_name("human");
   set_adj("watchful");
   set_long("This ordinary-looking man is carefully scanning his "+
      "surroundings, alert to any possible danger. The patch sewed onto his "+
      "right arm of two crossed swords indicates he is a member of the Kabal "+
      "city militia.\n");
   str = 50 + random(20);
   dex = 50 + random(20);
   con = 50 + random (10);
   set_stats(({str,dex,con,40,40,80}));
   set_alignment(250);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_act_time(12);
   add_act(({"say Isn't it time for a guard change now?","poke officer"}));
   add_act(({"ponder","emote grumbles: I want better payment for this job!"}));
   add_act("sigh");
   add_act("grumble");
   set_cact_time(6);
   add_cact("say You shouldn't have disturbed us. It will mean your death!");
   add_cact(({"say Wanna taste something sweet?",
      "emote licks his sword, tasting "+
      "the blood.","grin"}));
   add_cact("say If we kill you, we might get a raise in our payment!\n");
   add_speak("You're a bit too curious for your own good.\n");
   set_knight_prestige(-3);
   add_prop(LIVE_I_NEVERKNOWN, 1);
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Kalad/common/caravan/arm/cmscale");
   arm -> move(this_object());
   command("wear all");
   wep = clone_object("/d/Kalad/common/caravan/wep/cmsword");
   wep -> move(this_object());
   command("wield all");
   MONEY_MAKE_SC(random(30))->move(this_object(),1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("fume");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
