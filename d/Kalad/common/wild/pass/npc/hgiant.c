inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("giant");
   set_race_name("hill giant");
   set_adj("dull");
   set_long("A massive humanoid!\n"+
      "This being looks vaguely human in features, but that is where all "+
      "similarities end. He stands at least sixteen feet tall and walks "+
      "more in the fashion of an ape, than as a human.\n");
   set_stats(({175,75,125,50,50,100}));
   set_alignment(-50);
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   set_act_time(9);
   add_act("smile stupidly");
   add_act("duh");
   add_act("scratch behind");
   add_act("get all from corpse");
   set_cact_time(9);
   add_cact("say Me smash you like bug!");
   add_cact("say Me eat you for dinner!");
   add_speak("You know go away, me want to bash you.\n");
   set_knight_prestige(50);
   add_prop(CONT_I_WEIGHT,2000000);
   add_prop(CONT_I_VOLUME,2000000);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(TO));
   wep = clone_object("/d/Kalad/common/wild/pass/wep/gclub");
   wep -> move(TO);
   command("wield all");
   arm = clone_object("/d/Kalad/common/wild/pass/arm/gfur");
   arm -> move(TO);
   command("wear all");
   MONEY_MAKE_CC(random(100))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Now me eat you fer dinner, " + ob->query_nonmet_name() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
