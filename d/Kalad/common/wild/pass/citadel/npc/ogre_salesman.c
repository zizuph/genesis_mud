/* ogre_salesman */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Korat
 * The salesman in the citadel
 * Trades only with the evil folks
 */

/* angmar rumours */
#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"

void
create_monster()
{
   int i;
   ::create_monster();
   add_prop(DO_I_TELL_RUMOURS,1);
   set_name("ogre");
   set_race_name("ogre");
   set_adj("filthy");
   set_long("A middle-sized and disgustingly filthy brute of an ogre. "+
      "It doesn't look very pleased to see you here.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 50 + random(60));
   set_base_stat(3, 20);
   set_base_stat(4, 30);
   set_base_stat(5, 120);
   set_alignment(-400);
   set_knight_prestige(500);
   set_skill(SS_WEP_CLUB,70);
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,60);
   set_act_time(12);
   add_act("say Me rich!!");
   add_act("growl .");
   add_act("fart");
   add_act("hmm");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("snarl");
   add_cact("say Me have plenty things! Clubs!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   trig_new("%w 'drops' %s","react_drop");
}
void
arm_me()
{
   object item;
   seteuid(getuid(TO));
   command("wear all");
   item = clone_object(CPASS(wep/mol_club));
   item -> move(TO);
   command("wield all");
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
      command("fart");
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
   if (TO->query_hp()>0) return;
   
   command("say Urghh! Dem be hawd ta kill!!");
   ::do_die(enemy);
}

/* some functions to liven up selling and buying stuff here */
int
react_buy(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_buy",who);
      return 1;
   }
}
void
return_buy(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("say Me sell nice things to you! You thank me now ...");
      command("grin . " + (obj->query_real_name()));
   }
}
int
react_sell(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_sell",who);
      return 1;
   }
}
int
return_sell(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("poke " + (obj->query_real_name()));
      command("say Me poor now!");
   }
}
