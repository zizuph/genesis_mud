/* 
 * /d/Kalad/common/wild/pass/npc/d_brigand.c
 * Purpose    : A brigand in search of loot
 * Located    : /d/Kalad/common/wild/pass/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("brigand");
   set_race_name("human");
   set_adj("conniving");
   set_short("conniving brigand");
   set_pshort("conniving brigands");
   set_long("An unshaven human that smells strongly of liquor and the "+
      "outdoors. Clearly he must be eking out an existence in this harsh "+
      "desert, for his clothes are nothing but ragged tatters of cloth.\n");
   set_stats(({70,85,75,60,60,90}));
   set_aggressive(1);
   set_alignment(-250);
   set_skill(SS_WEP_CLUB,75);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_HIDE,60);
   set_act_time(9);
   add_act("smile greedily");
   add_act("say Gimme all yer loot!");
   add_act("say If ya don't gimme yer stuff, I'll have to beat you senseless!");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("say Now you're gonna get it!");
   add_cact("say The vultures will have a feast of yer corpse!");
   add_speak("Hello, gimme all yer loot...or I'll kill ya.\n");
   set_knight_prestige(250);
   trig_new("%w 'gives' 'you' %s", "react_leave");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep;
   seteuid(getuid(TO));
   wep = clone_object("/d/Kalad/common/wild/pass/wep/bclub");
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(10))->move(TO,1);
}
int
react_leave(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_leave",who);
      return 1;
   }
}
void
return_leave(string who) {
   object obj;
   int ran;
   if (obj = present(who, environment())) {
      command("smirk");
      command("say Thanks for the stuff, " + obj->query_nonmet_name() + ".");
      command("southeast");
      command("southeast");
      command("hide");
   }
}
