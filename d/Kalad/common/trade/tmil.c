inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(35);
   if (i < 3)
      return "reginald";
   else if (i < 6)
      return "boris";
   else if (i < 7)
      return "anth";
   else if (i < 8)
      return "james";
   else if (i < 9)
      return "charles";
   else if (i < 10)
      return "norwood";
   else if (i < 11)
      return "febbo";
   else if (i < 12)
      return "amrocar";
   else if (i < 13)
      return "andian";
   else if (i < 14)
      return "ulf";
   else if (i < 15)
      return "gorbel";
   else if (i < 16)
      return "brit";
   else if (i < 17)
      return "daniel";
   else if (i < 18)
      return "wilhelm";
   else if (i < 19)
      return "obbo";
   else if (i < 20)
      return "tandel";
   else if (i < 21)
      return "ardindel";
   else if (i < 22)
      return "mitus";
   else if (i < 23)
      return "linus";
   else if (i < 24)
      return "landil";
   else if (i < 25)
      return "kathin";
   else if (i < 26)
      return "baern";
   else if (i < 27)
      return "sehkmaa";
   else if (i < 28)
      return "joseph";
   else if (i < 29)
      return "dav";
   else if (i < 30)
      return "pieter";
   else if (i < 31)
      return "mikel";
   else if (i < 32)
      return "glen";
   else if (i < 33)
      return "erik";
   else
      
   return "fellir";
}
void
/* by Antharanos */
create_monster()
{
   string extra;
   extra = random_extra();
   set_name(extra);
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
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(TO));
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