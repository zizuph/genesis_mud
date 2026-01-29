inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
#include "/sys/filter_funs.h"

/* by Antharanos */
/* 2017-06-03 Malus: Removed name, added LIVE_I_NEVERKNOWN */

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
   set_stats(({55,50,55,40,40,50}));
   set_alignment(250);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_act_time(3);
   add_act("hmm");
   add_act("say Greetings traveller.");
   add_act("say Welcome to Kabal, our wonderful city.");
   add_act("emote carefully scans his surroundings.");
   set_cact_time(3);
   add_cact("say You will cease this senseless act now!");
   add_cact("say The city guards will kill you for this!");
   set_title("the Militiaman");
   set_random_move(10);
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
      command("shout No fighting in the streets, " + ob->query_nonmet_name() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
