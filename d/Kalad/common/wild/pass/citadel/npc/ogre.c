/* ogre.c */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   int i;
   ::create_monster();
   set_name("ogre");
   set_race_name("ogre");
   set_adj("filthy");
   set_long("A particularly large and disgustingly smelly brute of an ogre. "+
      "It doesn't look very pleased to see you here.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 75 + random(60));
   set_base_stat(3, 20);
   set_base_stat(4, 30);
   set_base_stat(5, 120);
   set_alignment(-400);
   set_knight_prestige(500);
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,40);
   set_act_time(12);
   add_act(({"say Ugly bugs!","kill dwarf"}));
   add_act("growl .");
   add_act("fart");
   add_act("roar");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("snarl");
   add_cact("say I crush you with rock!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
arm_me()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(obj/throw_rock));
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(wep/mol_club));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(5))->move(TO,1);
   MONEY_MAKE_CC(random(75))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Ye stupid " + TP->query_nonmet_name() + "!");
      command("say Me eat you now!");
      command("kill " + (ob->query_real_name()));
   }
}
public void
introduce_me(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("smirk");
      command("slap " + TP->query_real_name());
   }
}
int
react_drop(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("get all coins");
      command("grin greed");
   }
}

do_die(object enemy)
{
   object goliath;
   if (TO->query_hp()>0) return;
   
   command("say Urghh! Dem be hawd ta kill!!");
   goliath = present("goliath", E(TO));
   goliath ->command("say Fools! Now I have to kill'em myself!");
   goliath->command("kill "+lower_case(enemy->query_real_name()));
   ::do_die(enemy);
}
