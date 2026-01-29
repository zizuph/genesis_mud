inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("jeggred");
   add_name("patron");
   add_name("weaponmaster");
   add_name("master");
   set_race_name("drow");
   set_adj("thin");
   add_adj("destructive");
   set_long("A thin and almost emaciated-looking drow that nevertheless "+
      "seems to burn with a fierce inner fire. Murderous eyes dominate his "+
      "pinched face, further enhancing his already long-featured face.\n");
   set_extra_long("From the symbol of a sword and axe crossed over each "+
      "other on his forehead, it appears as if he belongs to House Claddath.\n");
   set_stats(({110,125,110,25,25,100}));
   set_alignment(-1000);
   set_skill(SS_WEP_AXE,99);
   set_skill(SS_WEP_CLUB,99);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,80);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_2H_COMBAT,90);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("emote gazes at you with fiery red eyes.");
   add_act("say Oloth zhah tuth abbil lueth ogglin.");
   add_act("say Sarn.");
   add_act("say Quarvalsharess zhah ultrin!");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_cact("say Claddath ultrin!");
   add_cact("say Claddath ulu usstan!");
   add_cact("command servantyr");
   set_knight_prestige(1000);
   add_speak("Leave now, before I slay you myself!\n");
   set_title("Claddath, the Patron and Weaponmaster of House Claddath");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}
void
init_living()
{
    ::init_living();
    if(interactive(TP))
       set_alarm(3.0,0.0,"return_attack",TP);
}

void
return_attack(object obj)
{
   if(present(obj, environment()))
      {
      command("say Elghinn plynn dos, iblith!");
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
   arm = clone_object(CPASS(drow/obj/h7_insignia));
   arm -> move(TO);
   wep = clone_object(CPASS(wep/dw_axe));
   wep -> move(TO);
   wep = clone_object(CPASS(drow/wep/h7_pat_mstar));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(15))->move(TO,1);
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
   hitresult = enemy->hit_me(325 + random(325), W_BLUDGEON, me, -1);
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