inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("drow");
   add_name("guard");
   add_name("guardian");
   set_race_name("drow");
   set_adj("ebony-skinned");
   add_adj("white-haired");
   set_short("drow guardian");
   set_pshort("drow guardians");
   set_long("Before you stands a being roughly five and a half feet in "+
      "height. His skin is the color of the surrounding rock, black as the "+
      "netherworld itself. In sharp contrast to this is the shock of white "+
      "hair that protrudes from his scalp, a feature that only seem to "+
      "highlight his angled elven features.\n");
   set_stats(({100,125,100,75,75,100}));
   set_alignment(-333);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,80);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_2H_COMBAT,75);
   set_act_time(6);
   add_act("emote scans his surroundings carefully.");
   add_act("say Oloth zhah tuth abbil lueth ogglin.");
   add_act("say Sarn.");
   add_act("say Quarvalsharess zhah ultrin!");
   add_act("say Sarn del Kabal, sarn del lil Thanarians.");
   add_act("smile grim");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_cact("say Undraeth Ultrinnan!");
   set_knight_prestige(666);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'clasps' 'you' 'by' 'the' 'forearms' 'in' 'the' 'Drow' %s","react_greet");
}
int
react_greet(string who)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_greet",who);
      return 1;
   }
}
void
return_greet(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Abban, elendar wun ulu bauthwaf.");
      obj->move_living("north","/d/Kalad/common/wild/pass/uc/u2");
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
   wep = clone_object(CPASS(wep/dw_axe));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(20))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Undraeth ultrinnan!");
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
