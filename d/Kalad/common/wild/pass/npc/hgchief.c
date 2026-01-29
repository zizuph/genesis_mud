/* 
 * /d/Kalad/common/wild/pass/npc/hgchief.c
 * Purpose    : Hill giant chief
 * Located    : /d/Kalad/common/wild/pass/huts
 * Created By : Antharanos ??.??.??
 * Modified By: Toby, 971014 (fixed typos)
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include  "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("skank");
   add_name("giant");
   add_name("chieftain");
   set_race_name("hill giant");
   set_adj("exceptional");
   set_long("A massive humanoid!\n"+
      "This hill giant looks every bit as dirty as the others, however he "+
      "looks like he is slightly more intelligent than they are, and "+
      "not to mention, much bigger.\n"+
      "He is twenty feet tall!\n");
   set_stats(({200,100,150,60,60,100}));
   set_alignment(-75);
   set_skill(SS_WEP_CLUB,90);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act("say I leader this village.");
   add_act("smile know");
   add_act("emote looks down at you from his lofty height.");
   add_act("scratch behind");
   add_act("smell vapors");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("say I smash you like ugly bug!");
   add_cact("say After me bash you, me put you in pot!");
   add_speak("You not leave now, then me and me giants bash you!\n");
   set_knight_prestige(150);
   set_title("the Chieftain");
   trig_new("%w 'arrives.' %s", "react_arrive");
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(this_object()));
   wep = clone_object("/d/Kalad/common/wild/pass/wep/gcclub");
   wep -> move(this_object());
   command("wield all");
   arm = clone_object("/d/Kalad/common/wild/pass/arm/gchide");
   arm -> move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(100))->move(TO,1);
}
int
react_arrive(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who) {
   object obj;
   int ran;
   if (obj = present(who, environment())) {
      command("grin .");
      command("say I smash you flat, then me have little " + obj->query_race_name() + " for dinner.");
      command("emote smacks his lips in anticipation.");
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Now I kill you and toss you in pot, " + ob->query_nonmet_name() + "!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}