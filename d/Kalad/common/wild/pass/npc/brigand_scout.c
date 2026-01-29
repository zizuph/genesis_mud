/* 
 * /d/Kalad/common/wild/pass/npc/brigand_scout.c
 * Purpose    : A brigand scout in search of loot
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
   set_adj("sneaky");
   set_short("sneaky brigand");
   set_long("An unshaven human that smells strongly of liquor and the "+
      "outdoors. Clearly he must be living in these surrounding forests, "+
      "since the clothes he wears are nothing but crudely sewn animal skins.\n");
   set_stats(({60,75,65,55,55,80}));
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
   set_cact_time(9);
   add_cact("say Now you're gonna get it!");
   add_cact("say The vultures will have a feast of yer corpse!");
   add_cact(({"west","examine shadows"}));
   add_speak("Hello, gimme all yer loot...or I'll kill ya.\n");
   set_knight_prestige(250);
   trig_new("%w 'gives' 'you' %s", "react_leave");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}
void
arm_me()
{
   object wep;
   seteuid(getuid(this_object()));
   wep = clone_object("/d/Kalad/common/wild/pass/wep/bclub");
   wep -> move(this_object());
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
      command("east");
      command("east");
      command("hide");
   }
}
