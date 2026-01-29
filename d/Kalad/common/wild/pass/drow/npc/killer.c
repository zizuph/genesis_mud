inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/extra_long";

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
   set_name("drow");
   add_name("warrior");
   set_race_name("drow");
   set_adj(extra);
   set_pshort(extra + " drow");
   set_long("A cold-blooded and completely ruthless warrior, one whose "+
      "body and mind have been wholly given to the ancient art of combat. "+
      "His glaring presence is only further heightened by the ebony-hue of "+
      "his skin and the glowing red eyes that stare out at you.\n"+
      "You face a member of the foul race of drow.\n");
   set_extra_long("From the symbol of a sword and axe crossed over "+
      "each other on his forehead, it appears as if he belongs to "+
      "House Claddath.\n");
   set_stats(({115,100,115,25,25,100}));
   set_alignment(-750);
   set_aggressive(1);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_WEP_AXE,90);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_2H_COMBAT,60);
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
   add_cact("say Claddath ultrin!");
   add_cact("say Claddath ulu usstan!");
   set_knight_prestige(750);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(CPASS(arm/dw_helm));
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
   hitresult = enemy->hit_me(225 + random(225), W_BLUDGEON, me, -1);
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
