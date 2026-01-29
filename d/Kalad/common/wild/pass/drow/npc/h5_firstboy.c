inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("solaufein");
   add_name("firstboy");
   set_race_name("drow");
   set_adj("cruel");
   add_adj("sadistic");
   set_long("A truly despicable example of a drow male, distinguished only "+
      "by the uncharacteristic look of control and patience visible in "+
      "his eyes.\n");
   set_extra_long("From the symbol of a sword crossed over a shield on "+
      "his forehead, it appears as if he belongs to House Kilsek.\n");
   set_stats(({100,125,100,25,25,100}));
   set_alignment(-1000);
   set_skill(SS_WEP_SWORD,95);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,75);
   set_skill(SS_BLIND_COMBAT,95);
   set_skill(SS_2H_COMBAT,75);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("emote looks long and carefully at you.");
   add_act("say Oloth zhah tuth abbil lueth ogglin.");
   add_act("say Sarn.");
   add_act("say Quarvalsharess zhah ultrin!");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_cact("say Kilsek ultrin!");
   add_cact("say Kilsek ulu usstan!");
   set_knight_prestige(1000);
   add_speak("You are not a member of House Kilsek! Leave quickly before "+
      "I kill you!\n");
   set_title("Kilsek, Firstboy of House Kilsek");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'starts' 'speaking' 'with' 'Solaufein' %s","react_attack");
}
int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(5.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Iblith!");
      command("kill " + (obj->query_real_name()));
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
   arm = clone_object(CPASS(arm/dw_shield));
   arm -> move(TO);
   command("wear all");
   arm = clone_object(CPASS(drow/obj/h5_insignia));
   arm -> move(TO);
   wep = clone_object(CPASS(drow/wep/undraeth_sword));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
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
   enemy -> catch_msg(QCTNAME(me) + " attempts to hit you in a vital spot!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to hit " + QTNAME(enemy) + " in a vital spot!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
