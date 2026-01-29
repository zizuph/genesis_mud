inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("drow");
   add_name("guard");
   set_race_name("drow");
   set_adj("wary");
   add_adj("suspicious");
   set_short("drow guard");
   set_pshort("drow guards");
   set_long("A warrior whose body is perfectly conditioned for the "+
      "brutal and savage art of war. His imposing presence is further "+
      "enhanced by the jet-black color of his skin, a feature that only "+
      "seems to highlight his elven features.\n"+
      "You face a member of the foul race of drow.\n");
   set_stats(({100,115,100,25,25,100}));
   set_alignment(-750);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,60);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_2H_COMBAT,90);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("emote scans his surroundings carefully.");
   add_act("say Oloth zhah tuth abbil lueth ogglin.");
   add_act("say Sarn.");
   add_act("say Quarvalsharess zhah ultrin!");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_speak("A minimum of one gold coin is required for traders to the "+
      "drow city of Undraeth. Give it to me and you may pass...you are a "+
      "trader, aren't you?\n");
   set_default_answer("You get no response from the drow guard.\n");
   set_knight_prestige(750);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_NEVERKNOWN,1);
   trig_new("%w 'gives' 'you' 'a' 'platinum' 'coin.\n' %s","react_pay");
   trig_new("%w 'gives' 'you' 'a' 'gold' 'coin.\n' %s","react_pay");
   trig_new("%w 'gives' 'you' '12' 'silver' 'coins.\n' %s","react_pay");
}
int
react_pay(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pay",who);
      return 1;
   }
}
void
return_pay(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("nod " + (obj->query_real_name()));
      obj -> move_living("east","/d/Kalad/common/wild/pass/drow/d5");
   }
}

void
emote_hook(string emote, object actor, string adverb)
{
   if (emote == "dgreet") set_alarm(1.0,0.0,"return_greet",actor);
}

void
return_greet(object who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("grin .");
      command("say Abban, elendar wun ulu Undraeth.");
      obj -> move_living("east","/d/Kalad/common/wild/pass/drow/d5");
   }
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_helm");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_chain");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/piwafwi");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_boots");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/wild/pass/wep/dw_sword");
   wep -> move(TO);
   wep = clone_object("/d/Kalad/common/wild/pass/wep/dw_sword");
   wep -> move(TO);
   command("wield all");
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
   hitresult = enemy->hit_me(300 + random(300), W_BLUDGEON, me, -1);
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
   me -> catch_msg("You attempt to hit your opponent in a vital spot!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
   enemy->catch_msg(QCTNAME(me) + " attempts to hit you in a vital spot!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to hit " + QTNAME(enemy) + " in a vital spot!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
