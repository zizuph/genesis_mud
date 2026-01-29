inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(10);
   if(i < 1)
      return "cruel";
   else if (i < 2)
      return "vicious";
   else if (i < 3)
      return "sadistic";
   else if (i < 4)
      return "savage";
   else if (i < 5)
      return "brutal";
   else if (i < 6)
      return "malevolent";
   else if (i < 7)
      return "demonic";
   else if (i < 8)
      return "devilish";
   else if (i < 9)
      return "unholy";
   else 
      return "hateful";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   string extra;
   extra = random_extra();
   set_name("aunrae");
   add_name("warrior");
   set_race_name("drow");
   set_adj(extra);
   add_adj("elite");
   set_pshort(extra + " elite drow");
   set_long("A stoic and completely emotionless face is all that you can "+
      "distinguish from the figure before you. Were it not for her occasional "+
      "movement she could easily be mistaken for a statue.\n");
   set_extra_long("From the symbol of a black widow spider perched atop "+
      "two crossed halberds, it appears as if she belongs to House Noquar.\n");
   set_gender(G_FEMALE);
   set_stats(({125,150,125,90,90,125}));
   set_alignment(-600);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_2H_COMBAT,60);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("emote paces before the compound's entrance.");
   add_act("glare all");
   add_act("emote gazes at you disinterestedly.");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_cact("shout Noquar ultrin!");
   set_knight_prestige(600);
   set_title("the Savage Raider of Undraeth");
   add_speak("Only those that show the insignia of House Noquar may "+
      "pass...that and those strong enough to get by me!\n");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'proudly' 'shows' 'the' 'insignia' 'of' 'House' 'Noquar.\n' %s","react_show");
   trig_new("%w 'proudly' 'shows' 'the' 'insignia' 'of' 'House' 'Claddath.\n' %s","react_block");
}
int
react_show(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_show",who);
      return 1;
   }
}
void
return_show(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("nod slightly " + (obj->query_real_name()));
      obj -> move_living("east","/d/Kalad/common/wild/pass/drow/house8/main_hall");
   }
}
int
react_block(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_block",who);
      return 1;
   }
}
void
return_block(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Elghinn ulu dos, darthiir!");
      command("kill " + (obj->query_real_name()));
   }
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(CPASS(drow/arm/h8_war_armour));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(CPASS(drow/wep/h8_war_halberd));
   wep -> move(TO);
   command("wield all");
   arm = clone_object(CPASS(drow/obj/h8_insignia));
   arm -> move(TO);
   MONEY_MAKE_GC(random(3))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Wael! Elghinn plynn dos!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;
   me = TO;
   if(random(15))
      return 0;
   hitresult = enemy->hit_me(250 + random(250), W_IMPALE, me, -1);
   how = " with little success";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 5)
      how = " bruisingly";
   if(hitresult[0] > 10)
      how = " painfully";
   if(hitresult[0] > 15)
      how = " very painfully";
   if(hitresult[0] > 20)
      how = " painfully hard";
   if(hitresult[0] > 25)
      how = " incredibly hard";
   if(hitresult[0] > 30)
      how = " with devastating effectiveness";
   if(hitresult[0] > 35)
      how = " with a fatal blow";
   me -> catch_msg("You attempt to impale your opponent!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to impale you with his weapon!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to impale " + QTNAME(enemy) + " with his weapon!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}